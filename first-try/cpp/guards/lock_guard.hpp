#ifndef _ILRD_RD743_LOCK_GUARD_HPP_
#define _ILRD_RD743_LOCK_GUARD_HPP_

namespace ilrd
{

template<typename Lockable>
class LockGuard
{    
public:
    explicit LockGuard(Lockable& lockable_);
    ~LockGuard();

private:
    Lockable& m_lockable;

    LockGuard(const LockGuard&);
    const LockGuard& operator=(const LockGuard&);
};

template<typename Lockable>
LockGuard<Lockable>::LockGuard(Lockable& lockable_)
    : m_lockable(lockable_)
{
    m_lockable.Lock();
}

template<typename Lockable>
LockGuard<Lockable>::~LockGuard()
{
    try
    {
        m_lockable.Unlock();
    }
    catch(...)
    {
        std::cerr << e.what() << '\n';
    }
}

} //namespace ilrd

#endif // _ILRD_RD743_LOCK_GUARD_HPP_