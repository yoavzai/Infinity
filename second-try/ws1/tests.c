#include <stdlib.h> //malloc, free
#include <stdio.h> //printf
#include <assert.h> //assert
#include "ws1.h"


static void TestTenToThe()
{
    assert(TenToThe(0) == 1);
    assert(TenToThe(1) == 10);
    assert(TenToThe(4) == 10000);
    assert(TenToThe(10) == 10000000000);
    assert(TenToThe(-1) == 0.1);
    assert(TenToThe(-4) == 0.0001);
    assert(TenToThe(-3) == 0.001);
}

static void TestFlip()
{
    assert(Flip(-540) == -45);
    assert(Flip(9) == 9);
    assert(Flip(9834) == 4389);
    assert(Flip(-123456) == -654321);
    assert(Flip(0) == 0);
}

static void TestSwap()
{
    int *x_p = (int*)malloc(sizeof(int));
    int *y_p = (int*)malloc(sizeof(int));
    int a = 1;
    int b = 2;
    *x_p = 3;
    *y_p = 4;

    Swap(x_p, y_p);
    assert(*x_p == 4);
    assert(*y_p == 3);
    Swap(&a, &b);
    assert(a == 2);
    assert(b == 1);
    Swap(x_p, &a);
    assert(*x_p == 2);
    assert(a = 4);
    
    free(x_p);
    free(y_p);
}

int main()
{
    PrintHelloHex();
    TestTenToThe();
    TestFlip();
    TestSwap();
    printf("All tests passed!\n");
    return 0;
}