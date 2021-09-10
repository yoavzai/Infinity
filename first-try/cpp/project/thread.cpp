#include <pthread.h> // p_thread
#include <cerrno>

#include "thread.hpp"
#include "thread_exception.hpp"

namespace ilrd
{

Thread::Thread(void*(*start_routine_)(void*), void* args_, Attr& attr_)
    : m_joinable(true)
{
    int return_val = pthread_create(&m_id, &attr_.attr, start_routine_, args_);

    switch (return_val)
    {
        case 0:
            return;

        case EINVAL:
            throw InvalidAttr();
            break;

        case EAGAIN:
            throw NoResource();
            break;

        case EPERM:
            throw NoPremission();
            break;

        default:
            throw ThreadException();
    }
}

Thread::~Thread()
{
    if (m_joinable)
    {
        //pthread_cancel(m_id);
        Join();
    }
}

void* Thread::Join()
{
    if (!m_joinable)
    {
        throw NonJoinable();
    }

    void* retval = NULL;

    int return_val = pthread_join(m_id, &retval);

    switch (return_val)
    {
        case 0:
            m_joinable = 0;
            return retval;

        case EINVAL:
            throw NonJoinable();
            break;

        case EDEADLK:
            throw Deadlock();
            break;

        default:
            throw ThreadException();
    }
}

void Thread::Detach()
{
    if (!m_joinable)
    {
        throw NonJoinable();
    }

    if (!pthread_detach(m_id))
    {
        m_joinable = 0;
    }
}

size_t Thread::GetID() const
{
    return m_id; 
}

Thread::Attr Thread::default_attr;

Thread::Attr::Attr()
{
    pthread_attr_init(&attr);
}

Thread::Attr::Attr(const pthread_attr_t& attr_)
    : attr(attr_)
{}

Thread::Attr::~Attr()
{
    pthread_attr_destroy(&attr);
}

} //namespace ilrd