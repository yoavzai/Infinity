#ifndef _DEADBEEF_
#define _DEADBEEF_

template<class T>
T* Deadbeef()
{
    return reinterpret_cast<T*>(0xDEADBEEF);
}

#endif