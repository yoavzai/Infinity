#ifndef _OLDSERVER_
#define _OLDSERVER_ 


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

#endif