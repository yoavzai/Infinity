#include <stdio.h>
#include <iostream>

struct Counter
{
    void Inc();
    void Dec();

    int m_a;
    int m_b;
};

void Counter::Inc()
{
    ++m_a;
    m_b += 2;
}

void Counter::Dec()
{
    --m_a;
    m_b /= 2;
}

int main()
{
    Counter x1;
    Counter x2;

    x1.m_a = 7;

    std::cout << "x1.m_a " << x1.m_a << " x1.m_b " << x1.m_b << std::endl;
    std::cout << "x2.m_a " << x2.m_a << " x2.m_b " << x2.m_b << std::endl;

    x2.m_a = 0;
    x2.m_b = 16;

    std::cout << "x1.m_a " << x1.m_a << " x1.m_b " << x1.m_b << std::endl;
    std::cout << "x2.m_a " << x2.m_a << " x2.m_b " << x2.m_b << std::endl;

    x1.Inc();
    x2.Dec();

    std::cout << "x1.m_a " << x1.m_a << " x1.m_b " << x1.m_b << std::endl;
    std::cout << "x2.m_a " << x2.m_a << " x2.m_b " << x2.m_b << std::endl;

    return 0;
}