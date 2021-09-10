#ifndef _ILRD_RD734_WAITABLE_QUEUE_HPP_
#define _ILRD_RD734_WAITABLE_QUEUE_HPP_

#include <boost/core/noncopyable.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


namespace ilrd
{

template<typename Container> 
class WaitableQueue : private boost::noncopyable
{
public:
    explicit WaitableQueue();
    ~WaitableQueue();

    void Push(typename Container::const_reference value_);

    void Pop(typename Container::reference outparam_);
    bool Pop(typename Container::reference outparam_, size_t timeout_);

private:
    Container m_queue;

    boost::interprocess::interprocess_mutex m_mutex;
    boost::interprocess::interprocess_semaphore m_semaphore;
};

template<typename Container> 
WaitableQueue<Container>::WaitableQueue()
    : m_semaphore(0)
{}

template<typename Container> 
WaitableQueue<Container>::~WaitableQueue()
{}

template<typename Container> 
void WaitableQueue<Container>::Push(typename Container::const_reference value_)
{
    m_mutex.lock();
    m_queue.push(value_);
    m_semaphore.post();
    m_mutex.unlock();
}

template<typename Container> 
void WaitableQueue<Container>::Pop(typename Container::reference outparam_)
{
    m_semaphore.wait();
    m_mutex.lock();
    outparam_ = m_queue.front();
    m_queue.pop();
    m_mutex.unlock();
}

template<typename Container> 
bool WaitableQueue<Container>::Pop(typename Container::reference outparam_, size_t timeout_)
{
    bool retval = false;

    time_t start_time = time(NULL);
    if (m_semaphore.timed_wait(boost::posix_time::second_clock::universal_time() +  
                            boost::posix_time::seconds(timeout_)))
    {
        if (m_mutex.timed_lock(boost::posix_time::second_clock::universal_time() +  
                            boost::posix_time::seconds(time(NULL)-start_time)))
        {
            outparam_ = m_queue.front();
            m_queue.pop();
            retval = true;
        }

        m_mutex.unlock();
    }

    return retval;
}

} // namespace ilrd

#endif // !_ILRD_RD734_WAITABLE_QUEUE_HPP_

