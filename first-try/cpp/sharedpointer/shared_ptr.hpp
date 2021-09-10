#ifndef _ILRD_RD734_SP_HPP_
#define _ILRD_RD734_SP_HPP_

#include <cstddef>

namespace ilrd
{

template <class T>
class SharedPtr
{
public:
    explicit SharedPtr(T* t_);
    SharedPtr(const SharedPtr& other_);
    template <typename S>
    SharedPtr(const SharedPtr<S>& other_);
    SharedPtr& operator=(const SharedPtr& other_);
    ~SharedPtr();
    T& operator*() const;
    T* operator->() const;
    size_t UseCount() const;

    template <typename S>
    friend class SharedPtr;

private:
    void CleanUp();
    T* m_ptr;
    size_t* m_cntr;
};

} // namespace ilrd

#include "shared_ptr.cpp"

#endif // _ILRD_RD734_SP_HPP_