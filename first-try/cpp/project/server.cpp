//  gd+ server.cpp fd_listener.cpp reactor.cpp thread.cpp stdin_cmd.cpp -I include -L. -llogger -Wl,-rpath,. -lboost_system -pthread -ldl -rdynamic

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <iostream>
#include <fstream>
#include <iosfwd>
#include <dlfcn.h>

#include "boost/lexical_cast.hpp"

#include "server.hpp"
#include "reactor.hpp"
#include "boost/shared_ptr.hpp" 
#include "udp_command.hpp"
#include "logger.hpp"
#include "singleton.hpp"
#include "stdin_cmd.hpp"

#define BACKLOG 10
#define WAIT_TIME 10
#define MSG_SIZE 30

namespace ilrd
{

inline bool Max(int x, int y)
{
	return (x > y ? x : y);
}

static int InitAddress(const char* wanted_ip, const char* port, addrinfo** server_info, 
                                int socket_type)
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = socket_type;

    if (wanted_ip == NULL)
    {
        hints.ai_flags = AI_PASSIVE;
    }

    return getaddrinfo(wanted_ip, port, &hints, server_info);
}

static int OpenSocket(addrinfo* node)
{
    return socket(node->ai_family, node->ai_socktype, node->ai_protocol);
}

static int BindSocket(int sockfd, addrinfo* node)
{
    return bind(sockfd, node->ai_addr, node->ai_addrlen);
}

static int GetSocket(struct addrinfo* server_info)
{
    int sockfd = 0;
    struct addrinfo* node = NULL;
    
    for (node = server_info; node != NULL; node = node->ai_next)    
    {
        sockfd = OpenSocket(node);

        if (sockfd == -1)
        {
            perror("socket fail");
            continue;
        }

        if (BindSocket(sockfd, node) == -1)
        {
            perror("bind fail");
            continue;
        }

        break;
    }

    freeaddrinfo(server_info);

    if (node == NULL)
    {
        fprintf(stderr, "server: failed to bind\n");

        return -1;
    }

    return sockfd;
}

static int SetSocket(const char* port, int socket_type)
{
    int status = 0;
    struct addrinfo* server_info = NULL;
    
    if ((status = InitAddress(NULL, port, &server_info, socket_type)) == -1)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        
        return -1;
    }

    return GetSocket(server_info);
}

/*********** STDIN ***********/

StdIn::StdIn(Reactor& reactor)
    : m_reactor(reactor), m_fd(STDIN_FILENO)
{
    m_factory.Add("exit", ExitCreator);
    m_factory.Add("+", PlusCreator);
    m_factory.Add("-", MinusCreator);
}

void StdIn::Connect()
{
    m_reactor.AddFD(m_fd, Reactor::READ, *this);
}

void StdIn::CleanUp()
{
    m_reactor.RemoveFD(m_fd, Reactor::READ);
}

void StdIn::operator()(void)
{
    Logger* log = Singleton<Logger>::Instance();
    log->Log(Logger::INFO, "StdIn operator");
    std::string buffer;
    std::getline(std::cin, buffer);

    try
    {
        boost::shared_ptr<StdinCmd> sp = m_factory.Create(buffer, &m_reactor);
        (*sp)();
    }
    catch(...)
    {
        log->Log(Logger::ERROR, "Invalid key");
    }
}

/*********** TCP_Single ***********/

TCP_Single::TCP_Single(int fd_, Reactor& reactor, Reactor::Mode mode_)
    : m_fd(fd_), m_reactor(reactor), m_mode(mode_)
{}

void TCP_Single::Connect()
{
    m_reactor.AddFD(m_fd, m_mode, *this);
}

void TCP_Single::CleanUp()
{
    close(m_fd);
    m_reactor.RemoveFD(m_fd, m_mode);
}

void TCP_Single::operator()(void)
{
    char buffer[MSG_SIZE];

    ssize_t nbytes = recv(m_fd, buffer, MSG_SIZE, 0);

    if (nbytes == 0 || nbytes == -1)
    {
        CleanUp();
        return;
    }

    buffer[nbytes + 1] = '\0';
    printf("%s\n", buffer);
    sleep(1);
    send(m_fd, "Pong", 4, 0);
}

/*********** TCP ***********/

TCP::TCP(Reactor& reactor, std::string port, Reactor::Mode mode_)
    : m_reactor(reactor), m_port(port), m_mode(mode_)
{}

bool TCP::Connect()
{
    m_fd = SetSocket(m_port.c_str(), SOCK_STREAM);
    
	if (m_fd == -1)
	{
		return false;
	}

    if (listen(m_fd, BACKLOG) == -1)
    {
        perror("listen");

        return false;
    }

    m_reactor.AddFD(m_fd, m_mode, *this);

    return true;
}

void TCP::CleanUp()
{
    close(m_fd);
    m_reactor.RemoveFD(m_fd, m_mode);
}

void TCP::operator()(void)
{
	struct addrinfo client_info;
    socklen_t addr_len = sizeof(client_info);

	int newfd = accept(m_fd, (struct sockaddr*)&client_info, &addr_len);

	if (newfd == -1)
	{
		perror("accept");
		return;
	}

    TCP_Single newtcp(newfd, m_reactor);
    newtcp.Connect();
}

/*********** UDP ***********/

UDP::UDP(Reactor& reactor, std::string port, Reactor::Mode mode_)
    : m_reactor(reactor), m_port(port), m_mode(mode_)
{
    Logger* log = Singleton<Logger>::Instance();

    void* read_handle = dlopen("./libread_cmd.so", RTLD_LAZY);
    if (read_handle == NULL)
    {
        log->Log(Logger::ERROR, dlerror());
        throw std::runtime_error(dlerror());
    }

    char(*read_get_key)() = (char(*)())dlsym(read_handle, "GetKey");
    if (read_get_key == NULL)
    {
        log->Log(Logger::ERROR, dlerror());
        throw std::runtime_error(dlerror());
    }
    
    boost::shared_ptr<Command>(*read_creator)(CmdData) =
        (boost::shared_ptr<Command>(*)(CmdData))dlsym(read_handle, "Creator");
    if (read_creator == NULL)
    {
        log->Log(Logger::ERROR, dlerror());
        throw std::runtime_error(dlerror());
    }

    void* write_handle = dlopen("./libwrite_cmd.so", RTLD_LAZY);
    if (write_handle == NULL)
    {
        log->Log(Logger::ERROR, dlerror());
        throw std::runtime_error(dlerror());
    }

    char(*write_get_key)() = (char(*)())dlsym(write_handle, "GetKey");
    if (write_get_key == NULL)
    {
        log->Log(Logger::ERROR, dlerror());
        throw std::runtime_error(dlerror());
    }

    boost::shared_ptr<Command>(*write_creator)(CmdData) =
        (boost::shared_ptr<Command>(*)(CmdData))dlsym(write_handle, "Creator");
    if (write_creator == NULL)
    {
        log->Log(Logger::ERROR, dlerror());
        throw std::runtime_error(dlerror());
    }

    m_factory.Add(read_get_key(), read_creator);
    m_factory.Add(write_get_key(), write_creator);
}

bool UDP::Connect()
{
    m_fd = SetSocket(m_port.c_str(), SOCK_DGRAM);
    
	if (m_fd == -1)
	{
		return false;
	}

    m_reactor.AddFD(m_fd, m_mode, *this);

    return true;
}

void UDP::CleanUp()
{
    close(m_fd);
    m_reactor.RemoveFD(m_fd, m_mode);
}

void UDP::operator()(void)
{
    Logger* log = Singleton<Logger>::Instance();
    log->Log(Logger::INFO, "UDP operator");
    char data[4114] = {0};
    struct addrinfo client_info;
    socklen_t addr_len = sizeof(client_info);
    
    recvfrom(m_fd, data, 4114, 0, (struct sockaddr*)&client_info, &addr_len);
    
    CmdData data_for_command(&client_info, &addr_len, &m_fd, data);

    try
    {
        (*(m_factory.Create(data[0], data_for_command)))();
    }
    catch(std::out_of_range)
    {
        log->Log(Logger::ERROR, "Invalid UDP command arrived");
    }
}

class LoggerInit
{
public:
    LoggerInit(const char* filename_) 
        : m_file(filename_), m_logger(Singleton<Logger>::Instance())
    {
        m_logger->SetOutputSeverity(Logger::DEBUG);
        m_logger->SetOutput(m_file);
        m_logger->Log(Logger::DEBUG, "Logger Ctor");
    }

    ~LoggerInit()
    {
        m_logger->Log(Logger::INFO, "Logger Dtor");
        sleep(1);
        m_logger->Exit();
        m_file.close();
    }

    std::ofstream m_file;
    Logger* m_logger;
};

} // namespace ILRD

/********** Main **********/

using namespace ilrd;

int main(int argc, char* argv[])
{
    assert(argc == 3);
    
    LoggerInit log("logger.log");

    Reactor reactor;
    StdIn std_in(reactor);
    TCP tcp(reactor, argv[1]);
    UDP udp(reactor, argv[2]);

    if (tcp.Connect() == false)
    {
        log.m_logger->Log(Logger::ERROR, "tcp connection error");
        return 1;
    }
    
    if (udp.Connect() == false)
    {
        log.m_logger->Log(Logger::ERROR, "udp connection error");
        return 1;
    }

    std_in.Connect();

    reactor.Run();

    return 0;
}