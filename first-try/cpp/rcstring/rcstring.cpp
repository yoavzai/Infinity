#include <cstring>

#include "rcstring.hpp"

namespace ilrd
{

inline size_t* AllocNewRCString(const char* cStr_)
{
    return reinterpret_cast<size_t*>(new char[sizeof(size_t) + strlen(cStr_) + 1]);
}

RCString::RCString(const char* cStr_)
    : m_counter(AllocNewRCString(cStr_)),
                m_cStr(reinterpret_cast<char*>(m_counter + 1))
{
    *m_counter = 1;
    strcpy(m_cStr, cStr_);
}

RCString::RCString(const RCString& other_)
    : m_counter(other_.m_counter), m_cStr(other_.m_cStr)
{
    ++(*m_counter);
}

RCString::~RCString()
{
    CleanupLast();
}

RCString& RCString::operator=(const RCString& other_)
{
    if (this->m_counter != other_.m_counter)
    {
        CleanupLast();

        m_counter = other_.m_counter;
        ++(*m_counter);
        m_cStr = other_.m_cStr;
    }

    return *this;
}

void RCString::CleanupLast()
{
    if (--(*m_counter) == 0)
    {
        delete[] m_counter;
    }
}

const char* RCString::GetCStr() const
{
    return m_cStr;
}

void RCString::SetChar(size_t idx_, char c_)
{
    m_cStr[idx_] = c_;
}

RCString::CharProxy::CharProxy(RCString& str_, size_t idx_)
    : m_origin(&str_), m_idx(idx_) 
{
}

RCString::CharProxy::~CharProxy()
{
}

char RCString::CharProxy::operator=(char ch)
{
    *m_origin = (*m_origin).GetCStr();
    (*m_origin).SetChar(m_idx, ch);

    return ch;
}

char RCString::CharProxy::operator=(CharProxy& other_)
{
    *m_origin = m_origin->GetCStr();
    m_origin->SetChar(m_idx, other_.m_origin->GetCStr()[other_.m_idx]);

    return m_origin->GetCStr()[m_idx];
}

RCString::CharProxy RCString::operator[](size_t index_)
{
    return RCString::CharProxy(*this, index_);    
}

RCString::CharProxy::operator char() const
{
    return (*m_origin).GetCStr()[m_idx];
}

size_t RCString::Length() const
{
    return strlen(m_cStr);
}

bool RCString::IsShared() const
{
    return *m_counter > 1;
}

char RCString::operator[](size_t index_) const
{
    return m_cStr[index_];
}

bool operator<(const RCString& lhs, const RCString& rhs)
{
    return strcmp(lhs.GetCStr(), rhs.GetCStr()) < 0;
}

bool operator>(const RCString& lhs, const RCString& rhs)
{
    return strcmp(lhs.GetCStr(), rhs.GetCStr()) > 0;
}

bool operator==(const RCString& lhs, const RCString& rhs)
{
    return strcmp(lhs.GetCStr(), rhs.GetCStr()) == 0;
}

bool operator!=(const RCString& lhs, const RCString& rhs)
{
    return strcmp(lhs.GetCStr(), rhs.GetCStr()) != 0;
}

std::ostream& operator<<(std::ostream& os, const RCString& rcStr)
{
    return os << rcStr.GetCStr();
}

} //namespace ilrd