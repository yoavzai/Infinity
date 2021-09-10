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

#define PORT "5555"
#define MSG_SIZE 30

int main()
{
    int i = 0;
    int status = 0;
    int sockfd = 0;
    struct addrinfo* server_info = NULL;
    struct addrinfo* node = NULL;
    char buffer[MSG_SIZE];
    struct addrinfo client_info;
    socklen_t addr_len = sizeof(client_info);

    if (status = InitAddress(NULL, PORT, &server_info, SOCK_DGRAM) == -1)
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

    printf("listener: waiting to recvfrom...\n");

    for (i = 0; i < 5; ++i)
    {
        recvfrom(sockfd, buffer, MSG_SIZE - 1, 0, (struct sockaddr*)&client_info, &addr_len);
        buffer[MSG_SIZE - 1] = '\0';
        printf("%s\n", buffer);

        sleep(1);
        sendto(sockfd, "Pong", MSG_SIZE, 0, (const struct sockaddr*)&client_info, addr_len);
    }

    close(sockfd);

    return 0;
}