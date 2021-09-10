#include <string.h>
#include <fstream>
#include <iostream>
#include <sys/socket.h>
#include <netdb.h>

#include "boost/lexical_cast.hpp"
#include "boost/shared_ptr.hpp"
#include "udp_command.hpp"
#include "logger.hpp"
#include "singleton.hpp"

namespace ilrd
{

extern "C"
{

class WriteRequest : public Command
{
public:
    WriteRequest(CmdData data_) : Command(data_) {};
    void operator()();
};

boost::shared_ptr<Command> Creator(CmdData data_)
{
    boost::shared_ptr<Command> nw(new WriteRequest(data_));
    return nw;
}

char GetKey()
{
    return 1;
}

void WriteRequest::operator()()
{
    Logger* log = Singleton<Logger>::Instance();
    log->Log(Logger::DEBUG, "entered WriteRequest operator");
    std::string filename = boost::lexical_cast<std::string>(*(size_t*)&data.m_data[9]);
    std::ofstream block(filename.c_str());

    data.m_data[9] = 0; //or 1 if oftream errors
    
    block.write(&data.m_data[17], 4096);
    sendto(*data.m_fd, data.m_data, 10, 0, (struct sockaddr*)data.m_client_info, *data.m_addr_len);
    block.close();
}

} // extern C
} // namespace ILRD