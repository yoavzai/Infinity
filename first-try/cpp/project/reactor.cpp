#include <map>

#include "reactor.hpp"
#include "fd_listener.hpp"

namespace ilrd
{

FDListener::FDVector Reactor::MapToVec()
{
    FDListener::FDVector vec;

    for (std::map<FDListener::ModeAndFD, Function>::const_iterator iter = m_fdToFuncs.begin(); 
                        iter != m_fdToFuncs.end(); ++iter)
    {
        vec.push_back(iter->first);
    }

    return vec;
}

Reactor::Reactor() : m_resume(true)
{}

void Reactor::Run()
{
    while (m_resume)
    {
        FDListener::FDVector temp_vec = this->MapToVec();
        temp_vec = m_listener.Wait(temp_vec);

        for (FDListener::FDVector::iterator iter = temp_vec.begin(); 
                        iter != temp_vec.end(); ++iter)
        {
            m_fdToFuncs[*iter]();
        }
    }
}

void Reactor::Stop()
{
    m_resume = false;
}

void Reactor::AddFD(int fd_, Mode mode_, Function func_)
{
    m_fdToFuncs[FDListener::ModeAndFD(fd_, (FDListener::Mode)mode_)] = func_;
}

void Reactor::RemoveFD(int fd_, Mode mode_)
{
    m_fdToFuncs.erase(FDListener::ModeAndFD(fd_, (FDListener::Mode)mode_));
}

} // namespace ILRD