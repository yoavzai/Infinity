#ifndef _COMMAND_
#define _COMMAND_

#include <netdb.h>

namespace ilrd
{

class CmdData
{
public:
    CmdData(addrinfo* client_info_, unsigned int* addr_len_, int* fd_, char* data_)
        : m_client_info(client_info_), m_addr_len(addr_len_), m_fd(fd_), m_data(data_) {};

    struct addrinfo* m_client_info;
    socklen_t* m_addr_len;
    int* m_fd;
    char* m_data;
};

class Command
{
public:
    Command(CmdData data_) : data(data_) {};

    virtual void operator()() = 0;
    CmdData data;
};

} // namespace ILRD

#endif

