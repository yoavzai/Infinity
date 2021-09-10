#include <stdio.h>

bool b1 = false;
bool b2;
int i = b2;

int main()
{
    printf("bool b1 %d\n", b1);
    printf("int initialized to b2 %d\n", i);

    b2 = i;

    printf("bool b2 assigned by int = false %d\n", b2);
    i = -1;
    b2 = i;
    printf("bool b2 assigned by int = -1 %d\n", b2);

    return 0;
}