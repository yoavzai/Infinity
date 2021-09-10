#include <stdio.h>
#include <stdlib.h>

int main()
{
    int j = 100;
    int* ptr = NULL;
    FILE* fp = fopen("Being Dumb", "w");
    fprintf(fp, "%p", &j);
    fclose(fp);

    return 0;
}