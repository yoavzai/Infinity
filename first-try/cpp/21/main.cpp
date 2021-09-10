#include <iostream>

using std::cout;
using std::endl;

class X
{
public:
    X(int a);
    bool operator==(const X& other) const;
    int GetValue() const;

private:
    int m_a;
};

X::X(int a)
    : m_a(a)
{}

bool X::operator==(const X& other) const
{
    return m_a == other.m_a;
}

int X::GetValue() const
{
    return m_a;
}

X operator+(const X& x1, const X& x2)
{
    return X(x1.GetValue() + x2.GetValue());
}

X operator-(const X& x, const X& y)
{
    return X(x.GetValue() - y.GetValue());
}

X operator*(const X& x, const X& y)
{
    return X(x.GetValue() * y.GetValue());
}

X operator!(const X& x)
{
    if (x.GetValue() == 1)
    {
        return x;
    }

    return x * (!(x - X(1)));
}


int main()
{
    X x1(3);
    X x2(6);

    cout << "x1 + x2: " << (x1 + x2).GetValue() << endl;
    cout << "x1 == x2: " << (x1==x2) << endl;
    cout << "!x2: " << (!x2).GetValue() << endl;
    return 0;
}
