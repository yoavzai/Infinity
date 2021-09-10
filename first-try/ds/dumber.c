#include <stdio.h>
#include <stdlib.h>

int main()
{
    int j = 200;
    int* ptr = NULL;
    FILE* fp = fopen("Being Dumb", "r");
    fscanf(fp, "%p", &ptr);
    printf("ptr %p\n&j %p\n",ptr, &j);
    printf("expected value 200\nactual value %d\n", *ptr);
    fclose(fp);

    return 0;
}