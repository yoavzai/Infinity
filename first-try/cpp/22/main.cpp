#include <iostream>

using std::cout;

inline void Foo()
{
    cout << "main\n";
}

int main()
{
    Foo();

    return 0;
}   