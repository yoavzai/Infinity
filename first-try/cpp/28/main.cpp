#include <iostream>

using namespace std;

const int a = 1;

void func(const int num)
{
    
    int* ip = (int*)&num;
    *ip = 5;

    cout << num << *ip << endl;
}

int main()
{
    const int b = 2;

    func(b);

    return 0;
}