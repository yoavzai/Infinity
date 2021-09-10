#include <stdio.h>


int main()
{
    char* str = "0123456789abcdef";
    char str2[17];

    printf("%s\n", Strcpy(str2, str));

    return 0;
}