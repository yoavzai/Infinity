#include <stdexcept>
#include <iostream>
#include <cstdlib>

using namespace std;

class A
{
public:
    A() {cout << "A ctor\n";}
    ~A() {cout << "A dtor\n";}
};

struct BadDog: public runtime_error
{
    BadDog(const string& s_="this is a bad dog")
        : runtime_error(s_) {}
};

void aaa()
{
    throw BadDog("bark");
}

void Fifi() throw(BadDog) {A a; throw logic_error("blah"); cerr<<"Fifi() after throw"<<endl;}
void Foo()  { Fifi(); cerr<<"Foo() after Fifi()"<<endl;}
void Bar(){ Foo(); cerr<<"Bar() after Foo()"<<endl;}

int main()
{
    try
    {
        
        Bar();
    }
    catch(BadDog& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    // try
    // {
    //     A a;
    //     Bar();
    // }
    // catch(bad_alloc)
    // {
    //     cout << "out of memory! exiting.\n"; exit(2);
    // }
    // catch(BadDog& b)
    // {
    //     cout << "BadDog exception: " << b.what() << endl; exit(3);
    // }
    // catch(exception& r)
    // {
    //     cout << " unknown exception: " << r.what() << endl; exit(4);
    // }
    // catch(...)
    // {
    //     cout << "generic" << endl;
    // }

    return 0;
}
