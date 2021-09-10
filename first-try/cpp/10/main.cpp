#include <stdio.h>

enum E1 {AA, BB, CC, DD};
enum E2 {TT, YY};

int i;

int main()
{
    E1 e;
    i = e;

    printf("%d\n", e);

    return 0;
}