#include "shared_ptr.hpp"
#include <iostream>

using std::cout;
using std::endl;
using namespace ilrd;

class A
{
public:
    A() {cout << "A Ctor\n";}
    ~A() {cout << "A Dtor";}
};

class B : public A
{
public:
    B() {cout << "B Ctor\n";}
    ~B() {cout << "B Dtor";}
};

int main()
{
    SharedPtr<B> derived(new B);
    SharedPtr<A> base(new B);

    base = derived;
    
    cout << "SharedPtr<A> base. count: " << base.UseCount() << endl;
    cout << "SharedPtr<B> derived. count: " << derived.UseCount() << endl;

    //base(derived);

    return 0;

}