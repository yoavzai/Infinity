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

#define PORT "5555"
#define MSG_SIZE 30
#define BACKLOG 10
/*
struct addrinfo {
        int              ai_flags;     // AI_PASSIVE, AI_CANONNAME, etc.
        int              ai_family;    // AF_INET, AF_INET6, AF_UNSPEC
        int              ai_socktype;  // SOCK_STREAM, SOCK_DGRAM
        int              ai_protocol;  // use 0 for "any"
        size_t           ai_addrlen;   // size of ai_addr in bytes
        struct sockaddr *ai_addr;      // struct sockaddr_in or _in6
        char            *ai_canonname; // full canonical hostname
    
        struct addrinfo *ai_next;      // linked list, next node
    };
*/

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

int main()
{
    int i = 0;
    int status = 0;
    int sockfd = 0;
    int newfd = 0;
    struct addrinfo* server_info = NULL;
    struct addrinfo* node = NULL;
    char buffer[MSG_SIZE];
    struct addrinfo client_info;
    socklen_t addr_len = sizeof(client_info);

    if (status = InitAddress(NULL, PORT, &server_info, SOCK_STREAM) == -1)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        
        return 1;
    }

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
        return 1;
    }

    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("listen");
        return 1;
    }

    printf("server, waiting for connection...\n");

    newfd = accept(sockfd, (struct sockaddr*)&client_info, &addr_len);

    if (newfd == -1)
    {
        perror("accept");
        return 1;
    }

    for (i = 0; i < 5; ++i)
    {
        recv(newfd, buffer, MSG_SIZE, 0);
        buffer[MSG_SIZE - 1] = '\0';
        printf("%s\n", buffer);
        sleep(1);
        send(newfd, "Pong", MSG_SIZE, 0);
    }

    close(newfd);
    close(sockfd);

    return 0;
}