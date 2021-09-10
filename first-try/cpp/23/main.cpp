#include <iostream> // std
#include <cstdlib> // size_t

using std::cout;
using std::endl;

class StaticCounter
{
public:
    static size_t StaticFunc(const StaticCounter& counter);
    StaticCounter();
    size_t GetId();

private:
    static size_t s_cntr;
    size_t m_id;
};

size_t StaticCounter::s_cntr = 0;

size_t StaticCounter::StaticFunc(const StaticCounter& counter)
{
    return counter.m_id; 
}

StaticCounter::StaticCounter()
    : m_id(++s_cntr)
{}


size_t StaticCounter::GetId()
{
    cout << m_id << endl;

    return m_id;
}

int main()
{
    StaticCounter x1;
    StaticCounter x2;

    x1.GetId();
    x2.GetId();

    cout << sizeof(StaticCounter) << endl;

    cout << "x1::m_id = " << x2.StaticFunc(x1);

    return 0;
}