#include <iostream>

#include "fraction.hpp"

using namespace ilrd;
using std::cout;
using std::endl;


int main()
{
    Fraction r1(1,2), r2(3);

    cout << r1 + r2 << endl;
    cout << r1 + 3 << endl;
    cout << 3 + r1 << endl;
    cout << r1 - r2 << endl;
    cout << r1 - 3 << endl;
    cout << 3 - r1 << endl;

    //cout << "f1 = " << ZERO - (f1 + ONE) << "\nf2 = " << f2 + HALF << endl;
//
    //double num = f1;
//
    //cout << num << endl;
//
    //cout << "n_instances = " << Fraction::NumOfInstances() << endl;
//
    //{
    //    Fraction r3;
    //    cout << "n_instances = " << Fraction::NumOfInstances() << endl;
    //}
//
    //cout << "n_instances = " << Fraction::NumOfInstances() << endl;
    
    //Fraction f1(1,2);
    //Fraction f2(3,2);
    //cout << "f1 = ";
    //f1.Print();
    //cout << "f1 == 1: " << (f1 == 1) << endl;
    //cout << "f2 = ";
    //f2.Print();
    //cout << "f1 += 1\n";
    //f1 += 1;
    //cout << "f1 = ";
    //f1.Print();
    //cout << "f1 == f2: " << (f1 == f2) << endl;
    //cout << "f2 += f1\n";
    //f2 += f1;
    //cout << "f2 = ";
    //f2.Print();
    //cout << "f2 == 3: " << (f2 == 3) << endl;
//
    //Fraction f3(-f2);
    //cout << "f3 = -f2\n";
    //cout << "f3 = ";
    //f3.Print();
//
    //cout << "f3 = +f1\n";
    //f3 = +f1;
    //cout << "f3 = ";
    //f3.Print();
    //cout << "\nf1 = ";
    //f1.Print();
    //cout << "f2 = ";
    //f2.Print();
    //cout << "\n+f1 + -(++f2) = ";
    //(+f1 + -(++f2)).Print();
    //cout << "\nf1 = ";
    //f1.Print();
    //cout << "f2 = ";
    //f2.Print();
    //cout << "\n(f1++) - +(f2--) = ";
    //((f1++) - +(f2--)).Print();
    //cout << "\nf1 = ";
    //f1.Print();
    //cout << "f2 = ";
    //f2.Print();
    //Fraction f2(4,8);
    //Fraction f3(4);
    //Fraction f4(0,0);
    //Fraction f5(36, 81);

    //cout << "f1 = ";
    //f1.Print();
    //cout << "f2 = ";
    //f2.Print();
    //cout << "f3 = ";
    //f3.Print();
    //cout << "f4 = ";
    //f4.Print();
    //cout << "f5 = ";
    //f5.Print();
//
    //cout << "f1 IsUndefined? " << f1.IsUndefined() << endl;
    //cout << "f4 IsUndefined? " << f4.IsUndefined() << endl;
    //cout << "f1 IsEqual to 0? " << f1.IsEqual(0) << endl;
    //cout << "f4 denom is " << f4.GetDenom() << endl;
    //cout << "f2 numer is " << f2.GetNumer() << endl;
//
    //f1 += f2;
    //cout << "f1 += f2\n" << "f1 == f2? " << f1.IsEqual(f2) << endl;
    //f5.AddToSelf(1);
    //f2 += f4;
    //cout << "f2 += f4\n";
    //cout << "f2 = ";
    //f2.Print();
    //cout << "f5 = ";
    //f5.Print();
    
    return 0;
}