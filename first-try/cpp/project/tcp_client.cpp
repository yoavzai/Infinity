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

#define TCP_PORT "6666"
#define MSG_SIZE 30
#define BACKLOG 10

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

int main()
{
    int i = 0;
    int status = 0;
    int sockfd = 0;
    struct addrinfo* server_info = NULL;
    struct addrinfo* node = NULL;

    if ((status = InitAddress(NULL, TCP_PORT, &server_info, SOCK_STREAM)) == -1)
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

        if (connect(sockfd, node->ai_addr, node->ai_addrlen) == -1)
        {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (node == NULL)
    {
        fprintf(stderr, "client: failed to connect\n");
        return 1;
    }

    freeaddrinfo(server_info);

    for (i = 0; i < 5; ++i)
    {
        sleep(1);
        char buffer[MSG_SIZE] = {0};
        send(sockfd, "Tcp Client", MSG_SIZE, 0);

        if (recv(sockfd, buffer, MSG_SIZE, 0) == 0)
        {
            break;
        }

        buffer[MSG_SIZE - 1] = '\0';
        printf("%s\n", buffer);
    }

    close(sockfd);

    return 0;
}