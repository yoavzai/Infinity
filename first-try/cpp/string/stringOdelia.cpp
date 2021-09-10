#include <cstring> /* string funcs */

#include "string.hpp" /* implement declared funcs */

ilrd::String::String(const char *str)
    : m_cstr(strcpy(new char[strlen(str) + 1], str))
{
}

ilrd::String::String(const String &other_)
    : m_cstr(strcpy(new char[strlen(other_.m_cstr) + 1], other_.m_cstr))
{
}

ilrd::String::~String()
{
    delete[] m_cstr;
}

ilrd::String &ilrd::String::operator=(const String &other_)
{
    delete[] m_cstr;
    m_cstr = new char[strlen(other_.m_cstr) + 1];
    strcpy(m_cstr, other_.m_cstr);

    return (*this);
}

size_t ilrd::String::Length() const
{
    return strlen(m_cstr);
}

const char *ilrd::String::CStr() const
{
    return m_cstr;
}

bool ilrd::operator==(const String &lhs, const String &rhs)
{
    return (strcmp(lhs.CStr(), rhs.CStr()) == 0);
}

bool ilrd::operator<(const String &lhs, const String &rhs)
{
    return (strcmp(lhs.CStr(), rhs.CStr()) < 0);
}

bool ilrd::operator>(const String &lhs, const String &rhs)
{
    return (strcmp(lhs.CStr(), rhs.CStr()) > 0);
}

std::ostream &ilrd::operator<<(std::ostream &os, const String &str)
{
    return (os << str.CStr());
}
