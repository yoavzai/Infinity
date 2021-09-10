#include <string.h>
#include <fstream>
#include <iostream>
#include <sys/socket.h>
#include <netdb.h>

#include "boost/lexical_cast.hpp"
#include "command.hpp"

namespace ilrd
{

CmdData::CmdData(addrinfo* client_info_, unsigned int* addr_len_, int* fd_, char* data_)
    : m_client_info(client_info_), m_addr_len(addr_len_), m_fd(fd_), m_data(data_)
{}

void WriteRequest::operator()()
{
    std::string filename = boost::lexical_cast<std::string>(*(size_t*)&data.m_data[9]);
    std::ofstream block(filename.c_str());

    data.m_data[9] = 0; //or 1 if oftream errors
    
    block.write(&data.m_data[17], 4096);
    sendto(*data.m_fd, data.m_data, 10, 0, (struct sockaddr*)data.m_client_info, *data.m_addr_len);
    block.close();
}

void ReadRequest::operator()()
{
    std::string filename = boost::lexical_cast<std::string>(*(size_t*)&data.m_data[9]);
    std::ifstream block(filename.c_str());

    data.m_data[9] = 0; //or 1 if iftream errors

    block.read(&data.m_data[10], 4096);
    sendto(*data.m_fd, data.m_data, 4106, 0, (struct sockaddr*)data.m_client_info, *data.m_addr_len);
    block.close();
}

Command* ReadCreator(CmdData data_)
{
    Command* nr = new ReadRequest(data_);
    return (nr);
}

Command* WriteCreator(CmdData data_)
{
    Command* nw = new WriteRequest(data_);
    return (nw);
}

} // namespace ILRD