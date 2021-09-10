#include <stddef.h> /* size_t */
#include <stdio.h> /* printf */

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define RESET "\x1b[0m"

void PrintArr(int *arr, int *C, size_t size)
{
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        if (arr + i == C)
        {
            printf(GREEN"%d"RESET, *(arr + i));
            continue;
        }
        printf("%d", *(arr + i));
    }

    puts("");
}

void BinnarySteadyInplaceSort(int *arr, size_t size)
{
    int *A = arr;
    int *B = NULL;
    int *C = NULL;
    int *end = arr + size;
    int tmp = 0;

    while (*A == 0 && A != end)
    {
        ++A;
    }

    B = A;

    while (1)
    {
        while (*B == 1 && B != end)
        {
            ++B;
        }

        if (B == end)
        {
            return;
        }

        C = B;

        while (C != A)
        {
            PrintArr(arr, C, size);
            usleep(300000);
            system("clear");
            tmp = *C;
            *C = *(C - 1);
            *(C-1) = tmp;
            --C;
        }
        PrintArr(arr, C, size);
        usleep(300000);
        system("clear");
        ++A;

        
    }
    PrintArr(arr, 0, size);
}


int main()
{
    int arr[] = {1,1,0,0,1,0,1,0,1,0,1,0,1,1,1,1,0};
    int arr2[] = {1,1,1,1,1,1,1,1};
    int arr3[] = {0,0,0,0,0,0,0,0,0};

    BinnarySteadyInplaceSort(arr, sizeof(arr)/sizeof(arr[0]));
 
    BinnarySteadyInplaceSort(arr2, sizeof(arr2)/sizeof(arr2[0]));
   
    
    BinnarySteadyInplaceSort(arr3, sizeof(arr3)/sizeof(arr3[0]));
   
    return 0;
}