#include <stdio.h>
#include <iostream>

struct Counter
{
    Counter* Inc();
    void Dec();

    int m_a;
    int m_b;
};

Counter* Counter::Inc()
{
    ++m_a;
    m_b += 2;

    return this;
}

void Counter::Dec()
{
    --m_a;
    m_b /= 2;
}

int main()
{
    Counter x1;

    x1.m_a = 7;

    std::cout << "x1.m_a " << x1.m_a << " x1.m_b " << x1.m_b << std::endl;

    x1.Inc()->Inc()->Inc();

    std::cout << "x1.m_a " << x1.m_a << " x1.m_b " << x1.m_b << std::endl;

    return 0;
}