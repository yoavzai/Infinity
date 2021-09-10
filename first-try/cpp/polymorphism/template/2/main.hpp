#ifndef _A_
#define _A_

template<class T>
class A
{
private:
    T m_a;
    T m_b;

public:
    A(T a, T b);
    T Getm_a();
    T Getm_b();
};

#include "main.cpp"

#endif