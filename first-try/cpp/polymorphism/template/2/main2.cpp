#include <iostream>

#include "main.hpp"

using namespace std;

int main()
{
    A<int> IntA(2, 4);
    A<double> DoubleA(2.2, 3.3);

    cout << IntA.Getm_a() << " " << IntA.Getm_b() << endl;
    cout << DoubleA.Getm_a() << " " << DoubleA.Getm_b() << endl;

    return 0;
}