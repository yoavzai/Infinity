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

#include "server.hpp"

#define MSG_SIZE 30
#define BACKLOG 10
#define MAX_TCP_THREADS 10
#define WAIT_TIME 10

static bool Exit = false;

void* TcpSingleRequest(void* arg)
{
    int newfd = *((int*)arg);
    int i = 0;
    char buffer[MSG_SIZE];

    while (!Exit)
    {
        if (recv(newfd, buffer, MSG_SIZE, 0) == 0)
        {
            break;
        }

        buffer[MSG_SIZE - 1] = '\0';
        //printf("%s\n", buffer);
        sleep(1);
        send(newfd, "Pong", MSG_SIZE, 0);
    }

    close(newfd);

    return NULL;
}

static int GetSocket(struct addrinfo* server_info)
{
    int sockfd = 0;
    struct addrinfo* node = NULL;
    struct timeval timeout;

    timeout.tv_sec = WAIT_TIME;
    timeout.tv_usec = 0;

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
        fprintf(stderr, "server: failed to bind\n");

        return -1;
    }

    return sockfd;
}

void* TcpMainThread(void* arg)
{
    pthread_t threads[MAX_TCP_THREADS] = {0};
    int thread_num = 0;
    int status = 0;
    int sockfd = 0;
    struct addrinfo* server_info = NULL;
    struct addrinfo client_info;
    socklen_t addr_len = sizeof(client_info);
   

    if (status = InitAddress(NULL, (char*)arg, &server_info, SOCK_STREAM) == -1)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        
        return NULL;
    }

    if ((sockfd = GetSocket(server_info)) == -1)
    {
        return NULL;
    }
    
    if (listen(sockfd, BACKLOG) == -1)
    {
        perror("listen");
        return NULL;
    }

    while (!Exit)
    {
        int newfd = accept(sockfd, (struct sockaddr*)&client_info, &addr_len);

        if (newfd == -1)
        {
            perror("accept");
            continue;
        }

        if (pthread_create(&threads[thread_num], NULL, TcpSingleRequest, &newfd) != 0)
        {
            perror("thread");
            continue;
        }
        
        ++thread_num;
    } 

    close(sockfd);

    while (thread_num > 0)
    {
        pthread_join(threads[thread_num - 1], NULL);
        --thread_num;
    }

    return NULL;
}

void* UdpMainThread(void* arg)
{
    int status = 0;
    int sockfd = 0;
    struct addrinfo* server_info = NULL;
    char buffer[MSG_SIZE];
    struct addrinfo client_info;
    socklen_t addr_len = sizeof(client_info);
   

    if (status = InitAddress(NULL, (char*)arg, &server_info, SOCK_DGRAM) == -1)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        
        return NULL;
    }

    if ((sockfd = GetSocket(server_info)) == -1)
    {
        return NULL;
    }

    while (!Exit)
    {
        recvfrom(sockfd, buffer, MSG_SIZE - 1, 0, (struct sockaddr*)&client_info, &addr_len);

        buffer[MSG_SIZE - 1] = '\0';
        //printf("%s\n", buffer);

        sleep(1);
        sendto(sockfd, "Pong", MSG_SIZE, 0, (const struct sockaddr*)&client_info, addr_len);
    }

    close(sockfd);

    return NULL;
}

int main(int argc, char* argv[])
{
    char str[MSG_SIZE] = {0}; 
    pthread_t tcp_thread;
    pthread_t udp_thread;

    if (argc != 3)
    {
        printf("enter ports!!!\n");

        return 1;
    }

    pthread_create(&tcp_thread, NULL, TcpMainThread, argv[1]);
    pthread_create(&udp_thread, NULL, UdpMainThread, argv[2]);

    do
    {
        fgets(str, MSG_SIZE, stdin);
    }
    while (strncmp(str, "exit", 4));

    Exit = true;

    pthread_join(tcp_thread, NULL);
    pthread_join(udp_thread, NULL);

    return 0;
}