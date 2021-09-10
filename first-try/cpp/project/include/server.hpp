#ifndef _SERVER_
#define _SERVER_

#include <string>

#include "boost/shared_ptr.hpp"
#include "reactor.hpp"
#include "factory.hpp"
#include "udp_command.hpp"
#include "stdin_cmd.hpp"

namespace ilrd
{

class StdIn
{
public:

    StdIn(Reactor& reactor);
    
    void Connect();
    void CleanUp();
    void operator()(void);

    Factory<boost::shared_ptr<StdinCmd>, std::string, Reactor*> m_factory;
    Reactor& m_reactor;
    int m_fd;
};

class TCP_Single
{
public:

    TCP_Single(int fd_, Reactor& reactor, Reactor::Mode mode_ = Reactor::READ);
    
    void Connect();
    void CleanUp();
    void operator()(void);

    int m_fd;
    Reactor& m_reactor;
    Reactor::Mode m_mode;
};

class TCP
{
public:

    TCP(Reactor& reactor, std::string port, Reactor::Mode mode_ = Reactor::READ);

    bool Connect();
    void CleanUp() ;
    void operator()(void);

    Reactor& m_reactor;
    std::string m_port;
    Reactor::Mode m_mode;
    int m_fd;
};

class UDP
{
public:
    UDP(Reactor& reactor, std::string port, Reactor::Mode mode_ = Reactor::READ);

    bool Connect();
    void CleanUp();
    void operator()(void);

    Factory<boost::shared_ptr<Command>, char, CmdData> m_factory;
    Reactor& m_reactor;
    std::string m_port;
    Reactor::Mode m_mode;
    int m_fd;
};

} // namespace ILRD

#endif