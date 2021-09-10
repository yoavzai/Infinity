#ifndef _ILRD_RD734_REACTOR_HPP_
#define _ILRD_RD734_REACTOR_HPP_

#include <map>

#include "fd_listener.hpp"

namespace ilrd
{
    
class Reactor
{
public:
    typedef boost::function<void(void)> Function;
    enum Mode {READ, WRITE, EXCEPT};

    Reactor();
    //~Reactor() = default

    void Run();
    void Stop();
    void AddFD(int fd_, Mode mode_, Function func_);
    void RemoveFD(int fd_, Mode mode_);
    
private:
    bool m_resume;
    FDListener m_listener;
    FDListener::FDVector MapToVec();
    std::map<FDListener::ModeAndFD, Function> m_fdToFuncs;
};

} // namespace ilrd

#endif // !_ILRD_RD734_REACTOR_HPP_