#include <stdio.h>

#include "calculate.h"

int main()
{
    char* str[] = {"2*2^3-16", "8(((+8)))*3+-2^5", "8+((8*3)-2)^", "2/0", "8++8*(((3-2)*5))", "(3-2)*5^0", "(3-2)*5+ 5*(4+4+4"};
    double result = 0;
    size_t i = 0;
    status_t calc = 0;

    for (i = 0; i < sizeof(str)/sizeof(str[0]); ++i)
    {
        calc = Calculate(str[i], &result);
        printf("Resault = %f, Status = %d\n", result, calc);
    }

    return 0;
}