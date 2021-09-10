#include <iostream>
#include "shared_ptr.hpp"

namespace ilrd
{

template <class T>
SharedPtr<T>::SharedPtr(T* t_)
    : m_ptr(t_), m_cntr(new size_t(1))
{
}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr& other_)
    : m_ptr(other_.m_ptr), m_cntr(other_.m_cntr)
{
    ++(*m_cntr);
}

template <class T>
template <typename S>
SharedPtr<T>::SharedPtr(const SharedPtr<S>& other_)
    : m_ptr(other_.m_ptr), m_cntr(other_.m_cntr)
{
    ++(*m_cntr);
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other_)
{
    this->~SharedPtr();

    m_ptr = other_.m_ptr;
    m_cntr = other_.m_cntr;
    ++(*m_cntr);

    return *this;
}

template <class T>
SharedPtr<T>::~SharedPtr()
{
    if (--(*m_cntr) == 0)
    {
        CleanUp();
    }
}

template <class T>
void SharedPtr<T>::CleanUp()
{
    delete m_ptr;
    delete m_cntr;
    m_ptr = NULL;
    m_cntr = NULL;
}

template <class T>
size_t SharedPtr<T>::UseCount() const
{
    return *m_cntr;
}

template <class T>
T& SharedPtr<T>::operator*() const
{
    return *m_ptr;
}

template <class T>
T* SharedPtr<T>::operator->() const
{
    return m_ptr;
}

} // namespace ilrd