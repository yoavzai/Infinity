#include <vector>
#include <boost/chrono.hpp>
#include <boost/function.hpp>
#include <iostream>
#include <string>

#include "logger.hpp"
#include "singleton.hpp"
#include "fd_listener.hpp"
#include "boost/lexical_cast.hpp"

using std::cout;
using std::endl;

namespace ilrd
{

const boost::chrono::milliseconds FDListener::s_timeout(2000);

inline int Max(int x, int y)
{
    return (x > y ? x : y);
}

static void SetReadyVector(FDListener::FDVector* ready, 
                                            fd_set* sets, int maxfd)
{
    for(int i = 0; i <= maxfd; ++i)
    {
        if (FD_ISSET(i ,&sets[FDListener::READ]))
        {
            ready->push_back(FDListener::ModeAndFD(i, FDListener::READ));
        }
        else if (FD_ISSET(i ,&sets[FDListener::WRITE]))
        {
            ready->push_back(FDListener::ModeAndFD(i, FDListener::WRITE));
        }
        else if (FD_ISSET(i ,&sets[FDListener::EXCEPT]))
        {
            ready->push_back(FDListener::ModeAndFD(i, FDListener::EXCEPT));
        }
    }
}

FDListener::FDVector FDListener::Wait(FDVector& fds_)
{
    Logger* log = Singleton<Logger>::Instance();
    
    int maxfd = 0;
    struct timeval timeout;

    fd_set sets[3];
    FD_ZERO(&sets[0]);
    FD_ZERO(&sets[1]);
    FD_ZERO(&sets[2]);
    
    FDListener::FDVector ready;

    timeout.tv_sec = 0;
    timeout.tv_usec = s_timeout.count() * 1000;

    for (FDVector::iterator itr = fds_.begin(); itr != fds_.end(); itr++)
    {
        FD_SET(itr->first ,&sets[itr->second]);
        maxfd = Max(maxfd, itr->first);
    }

    if (select(maxfd + 1, &sets[READ], &sets[WRITE], &sets[EXCEPT], &timeout) == -1)
    {
        log->Log(Logger::ERROR, "select" + std::string(strerror(errno)));
        
        throw std::runtime_error("select");
    }

    SetReadyVector(&ready ,sets, maxfd);

    return ready;
}

} // namespace ILRD

