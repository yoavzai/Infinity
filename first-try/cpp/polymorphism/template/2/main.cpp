
#include "main.hpp"

template<class T>
A<T>::A(T a, T b)
    : m_a(a), m_b(b)
{
}

template<class T>
T A<T>::Getm_a()
{
    return m_a;
}

template<class T>
T A<T>::Getm_b()
{
    return m_b;
}

