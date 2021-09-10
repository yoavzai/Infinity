#include <stdio.h>

struct Counter
{
    void Inc();
    void Dec();

    int m_a;
    int m_b;
};

struct X
{
    explicit X();
    explicit X(int a_, int b_ = 1);
    ~X();
    X(const X& other_);
    X& operator=(const X& other_);

    int m_a;
    int m_b;
};

struct Y
{
    X m_x;
    int m_i;
};

X::X()
    : m_a(3), m_b(4)
{
    printf("Default Ctor: %p, %d, %d\n", (void*)this, m_a, m_b);
}

X::X(int a_, int b_)
    : m_a(a_), m_b(b_)
{
    printf("Ctor(int, int): %p, %d, %d\n", (void*)this, m_a, m_b);
}

X::X(const X& other_)
    : m_a(other_.m_a) ,m_b(other_.m_b)
{
    printf("CCtor: %p, %d, %d\n", (void*)this, m_a, m_b);
}

X& X::operator=(const X& other_)
{
    m_a = other_.m_a;
    printf("Copy: %p, %d, %d\n", (void*)this, m_a, m_b);

    return *this;
}

X::~X()
{
    printf("Dtor: %p, %d, %d\n", (void*)this, m_a, m_b);
}
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
    float* f = new float(12.6);
    delete f;

    f = new float[15];
    delete[] f;

    Counter* c1 = new Counter;
    X* x1 = new X;
    Y* y1 = new Y;

    delete y1;
    delete c1;
    delete x1;
    
    X* xp = new X[10];
    delete[] xp;
}