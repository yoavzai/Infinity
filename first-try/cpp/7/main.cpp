#include <stdio.h>


struct Big
{
    int x;
};

void Foo(int num)
{
    num = 5;
}

void Foo(const Big& big_ref)
{
    ((Big&)big_ref).x = 2;
}

Big big;

int main()
{
    int num = 4;
    big.x = 1;
    Foo(big);
    Foo(num);

    printf("%d\n", big.x);

    return 0;
}