#include <iostream>
#include <typeinfo>

#include "factory.hpp"
#include "serializer.hpp"

using std::cout;
using std::endl;

class Base
{
public:
    Base() {}
    int m_i;
};

class Derived : public Base
{
public:
    Derived() {}
    double m_d;
};

int main()
{
    Base* b1 = new Base;
    Base* b2 = new Base;


    cout << "type id of b1: " << typeid(b1).name() << endl;
    cout << "type id of b2: " << typeid(b2).name() << endl;

    return 0;
}
