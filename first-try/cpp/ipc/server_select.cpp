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

#include "fd_listener.hpp"

#define BUFFER_SIZE 1024
#define BACKLOG 10
#define WAIT_TIME 10

static bool resume = 1;

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
    int sockfd = 0;
    struct addrinfo* server_info = NULL;
    struct addrinfo client_info;
    socklen_t addr_len = sizeof(client_info);
   

    if (status = InitAddress(NULL, port, &server_info, socket_type) == -1)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        
        return -1;
    }

    if ((sockfd = GetSocket(server_info)) == -1)
    {
        return -1;
    }

	return sockfd;
}

static void TcpNewConection(int fd, int* maxfd, fd_set* master)
{
	struct addrinfo client_info;
    socklen_t addr_len = sizeof(client_info);

	int newfd = accept(fd, (struct sockaddr*)&client_info, &addr_len);

	if (newfd == -1)
	{
		perror("accept");
		return;
	}

	FD_SET(newfd, master);

	*maxfd = Max(*maxfd, newfd);
}

static void UdpRoutine()()
{
    while (!Exit)
    {
        recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr*)&client_info, &addr_len);

        buffer[BUFFER_SIZE - 1] = '\0';
        //printf("%s\n", buffer);

    
        sendto(sockfd, "Pong", BUFFER_SIZE, 0, (const struct sockaddr*)&client_info, addr_len);
    }

    close(sockfd);

    return NULL;
}

static void SetTimeout(struct timeval* timeout)
{
    timeout->tv_sec = WAIT_TIME;
    timeout->tv_usec = 0;
}

inline bool Max(int x, int y)
{
	return (x > y ? x : y);
}

int main(int argc, char* argv[])
{
	int tcp_fd = 0;
	int udp_fd = 0;
    int std_in = STDIN_FILENO;


	if (udp_fd = SetSocket(argv[2], SOCK_DGRAM) == -1)
	{
		return 1;
	}

	if (tcp_fd = SetSocket(argv[1], SOCK_STREAM) == -1)
	{
		return 1;
	}

	if (listen(tcp_fd, BACKLOG) == -1)
    {
        perror("listen");
        return 1;
    }

	while (resume)
	{

		if (select(maxfd + 1, &readfds, NULL, NULL, &timeout) == -1)
		{
			perror("select");
            return 1;
		}

		for(i = 0; i <= maxfd; ++i)
		{
			if (FD_ISSET(i, &readfds))
			{
				switch (i)
				{
					case udp_fd:
						UdpRoutine(i);
						break;
					
					case tcp_fd:
						TcpNewConection(i, &maxfd, &master);
						break;
					
					case STDIN_FILENO:
						StdinRoutine(i);
						break;
					
					default:
						TcpNewMessage(i);
				}
			}
		}

    return 0;
}