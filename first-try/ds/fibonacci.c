#include <stdio.h>

int Fibonacci(unsigned int n)
{
    if (n == 1 || n == 2)
    {
        return 1;
    }

    return Fibonacci(n - 1)  + Fibonacci(n - 2);
}

int main()
{
    printf("%u\n%u\n%u\n", Fibonacci(10), Fibonacci(20), Fibonacci(30));

    return 0;
}