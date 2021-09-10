
#include <stdio.h>
#include <string.h>
#include "ws1.h"


int PrintHelloHex()
{
    char str1[] = "\x22\x48\x65\x6C\x6C\x6F\x21\x22";
    printf("%s\n",str1);   
}


double TenToThe(int n)
{
    int i;
    double res = 1;

    if (n > 0)
    {
        for (i=0; i<n; ++i)
        {
            res *= 10;
        }
    }

    //n = -5 and lower causes a rounding problem
    else if (n < 0)
    {
        for (i=0; i>n; --i)
        {
            res /= 10;
        }
    }
    
    return res;
}


int Flip(int n)
{
    int sign = (n >= 0 ? 1 : -1);
    int res = 0;
    //make n postive
    n *= sign;

    while (n != 0)
    {
        res *= 10;
        res += n % 10;
        n /= 10;
    }

    return res*sign;
}


void Swap(int *num1, int *num2)
{
    int tmp = *num1;
    *num1 = *num2;
    *num2 = tmp;
}
