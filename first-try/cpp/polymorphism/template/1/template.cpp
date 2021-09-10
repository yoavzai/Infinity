#include <iostream>
#include <cstdio>

using namespace std;

//#include "template.hpp"

template <typename T>
T Max(T t1, T t2)
{
    return t1 > t2 ? t1 : t2;
}

template <class U>
U Min(U t1, U t2)
{
    return t1 < t2 ? t1 : t2;
}

int main()
{

    cout << Min(1,2) << endl;
    cout << Max(1,2) << endl;


    //int arr[12];

    //printf("%p\n", Max<char>('a', 'b'));
    //std::cout << Max(3,5) << " " << Max<double>(3.7,12.9) << " ";
    //std::cout << Max<int*>(arr, arr + 8) << std::endl;
    //std::cout << Max('a', 'b') << std::endl;

    //Foo();

    return 0;
}