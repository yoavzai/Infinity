#include <stdio.h>

#include "heap.h"

#define RED "\033[22;31m"
#define GREEN "\033[22;32m"
#define RESET "\x1B[0m"
#define REQUIRE(x,y) (x == y ? printf(GREEN"SUCCESS\n"RESET) : printf(RED"FAIL\n"RESET))

int cmp_func(const void* data1, const void* data2)
{
    return *(int*)data1 - *(int*)data2;
}

int main()
{
    size_t i = 0;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    heap_t* heap = HeapCreate(cmp_func);

    REQUIRE(HeapSize(heap), 0);
    REQUIRE(HeapIsEmpty(heap), 1);
    
    /*
    for (i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
    {
        HeapPush(heap, arr + i);
        printf("peek: %d\n", *(int*)HeapPeek(heap));
        puts("");
        PrintHeap(heap);
        printf("-----------------\n");
    }
    */

    HeapPush(heap, arr + 8);
    HeapPush(heap, arr + 7);
    HeapPush(heap, arr + 2);
    HeapPush(heap, arr + 6);
    HeapPush(heap, arr + 5);
    HeapPush(heap, arr + 1);
    HeapPush(heap, arr + 0);
    HeapPush(heap, arr + 4);
    HeapPush(heap, arr + 3);

    PrintHeap(heap);
    printf("-----------------\n");

    HeapRemove(heap, arr + 0, cmp_func);
    PrintHeap(heap);
    printf("-----------------\n");

    HeapRemove(heap, arr + 1, cmp_func);
    PrintHeap(heap);
    printf("-----------------\n");

    for (i = 2; i < sizeof(arr) / sizeof(arr[0]); ++i)
    {
        printf("peek: %d\n", *(int*)HeapPeek(heap));
        HeapPop(heap);
        puts("");
        PrintHeap(heap);
        printf("-----------------\n");
    }

    HeapRemove(heap, arr + 1, cmp_func);
    HeapPop(heap);
    PrintHeap(heap);
    printf("-----------------\n");

    HeapDestroy(heap);

    return 0;
}