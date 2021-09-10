#include <cstdlib> // size_t
#include <iostream> // std::ostream
#include <cstring> // strlen, strcpy

#include "string.hpp"

namespace ilrd
{

inline char* InitStr(const char* src)
{
    char* dest = new char[strlen(src) + 1];
    strcpy(dest, src);

    return dest;
}

String::String(const char* str)
    : m_cstr(InitStr(str))
{
}
    
String::String(const String& other_)
    : m_cstr(InitStr(other_.m_cstr))
{ 
}

String::~String()
{
    delete[] m_cstr;
}

String& String::operator=(const String& other_)
{
    delete[] m_cstr;
    m_cstr = InitStr(other_.m_cstr);

    return *this;
}

size_t String::Length() const
{
    return strlen(m_cstr);
}

const char* String::CStr() const
{
    return m_cstr;
}

bool operator==(const String& lhs, const String& rhs)
{
    return strcmp(lhs.CStr(), rhs.CStr()) == 0;
}

bool operator<(const String& lhs, const String& rhs)
{
    return strcmp(lhs.CStr(), rhs.CStr()) < 0;
}

bool operator>(const String& lhs, const String& rhs)
{
    return strcmp(lhs.CStr(), rhs.CStr()) > 0;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
    return (os << str.CStr()); 
}

}// namespace ilrd