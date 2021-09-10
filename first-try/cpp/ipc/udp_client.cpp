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

#include "server.hpp"

#define UDP_PORT "5555"
#define MSG_SIZE 30

int main()
{
    int i = 0;
    int status = 0;
    int sockfd = 0;
    struct addrinfo* server_info = NULL;
    struct addrinfo* node = NULL;
    char buffer[MSG_SIZE];
    struct timeval timeout;

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    if (status = InitAddress(NULL, UDP_PORT, &server_info, SOCK_DGRAM) == -1)
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
        
        if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) != 0)
        {
            close(sockfd);
            printf("timout fail\n");
            continue;
        }

        break;
    }

    freeaddrinfo(server_info);

    if (node == NULL)
    {
        fprintf(stderr, "failed to connect\n");
        return 1;
    }

    for (i = 0; i < 5; ++i)
    {
        sleep(1);
        sendto(sockfd, "Ping", MSG_SIZE, 0, node->ai_addr, node->ai_addrlen);
        if (recvfrom(sockfd, buffer, MSG_SIZE - 1, 0, node->ai_addr, &node->ai_addrlen) == -1)
        {
            break;
        }

        buffer[MSG_SIZE - 1] = '\0';
        printf("%s\n", buffer);
    }

    close(sockfd);

    return 0;
}