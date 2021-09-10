#include <stdio.h> /* printf */
#include <string.h> /* memcmp memcpy */
#include <stdlib.h> /* rand, qsort */
#include <time.h> /* time */

#include "sorts.h"

#define SIZE 100000
#define RANGE 100000

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define RESET "\x1b[0m"
#define REQUIRE(cond) ((cond) ? printf(GREEN"SUCCESS\n"RESET) : printf(RED"FAIL\n"RESET))

/************************************************/

static int cmp_func(const void* data1,const void* data2)
{
    return *(int*)data1 - *(int*)data2;
}

static void Print(int* arr, size_t size)
{
    while (size > 0)
    {
        printf("%d ", *arr);

        arr++;
        size--;
    }
    puts("");
}

static void RandomsArr(int* arr, int lower, int upper, int count) 
{ 
    int i = 0;

    srand(time(NULL));

    for (i = 0; i < count; i++)
    { 
        arr[i] = (rand() % (upper - lower + 1)) + lower;
    } 
}

static int Comp(const void* num1, const void* num2)
{
    return (*(int*)num1 - *(int*)num2);
}

int main()
{
    time_t t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
    int Qsort[SIZE], Bubble[SIZE], Insertion[SIZE], Selection[SIZE], Counting[SIZE], CountingDest[SIZE],
        Radix1[SIZE], Radix2[SIZE], Merge[SIZE], MergeDest[SIZE], Heap[SIZE], Quick[SIZE];
    RandomsArr(Bubble, 0, RANGE, SIZE);
    memcpy(Qsort, Bubble, SIZE * sizeof(int));
    memcpy(Insertion, Bubble, SIZE * sizeof(int));
    memcpy(Selection, Bubble, SIZE * sizeof(int));
    memcpy(Counting, Bubble, SIZE * sizeof(int));
    memcpy(Radix1, Bubble, SIZE * sizeof(int));
    memcpy(Radix2, Bubble, SIZE * sizeof(int));
    memcpy(Merge, Bubble, SIZE * sizeof(int));
    memcpy(Heap, Bubble, SIZE * sizeof(int));
    memcpy(Quick, Bubble, SIZE * sizeof(int));

    t0 = clock();
    qsort(Qsort, SIZE, sizeof(int), Comp);
    t1 = clock();
    BubbleSort(Bubble, SIZE);
    t2 = clock();
    InsertionSort(Insertion, SIZE);
    t3 = clock();
    SelectionSort(Selection, SIZE);
    t4 = clock();
    CountingSort(Counting, CountingDest, SIZE, 0, RANGE);
    t5 = clock();
    RadixSort(Radix1, SIZE, 2);
    t6 = clock();
    RadixSort(Radix2, SIZE, 10);
    t7 = clock();
    MergeSort(MergeDest, Merge, SIZE);
    t8 = clock();
    HeapSort(Heap, SIZE);
    t9 = clock();
    QuickSort(Quick, sizeof(int), SIZE, cmp_func);
    t10= clock();

    printf("Qsort: %f\n", (double)(t1 - t0) / CLOCKS_PER_SEC);
    printf("Bubble: %f ", (double)(t2 - t1) / CLOCKS_PER_SEC);
    REQUIRE(memcmp(Bubble, Qsort, SIZE*sizeof(int)) == 0);
    printf("Insertion: %f ", (double)(t3 - t2) / CLOCKS_PER_SEC);    
    REQUIRE(memcmp(Insertion, Bubble, SIZE*sizeof(int)) == 0);
    printf("Selection: %f ", (double)(t4 - t3) / CLOCKS_PER_SEC);    
    REQUIRE(memcmp(Selection, Bubble, SIZE*sizeof(int)) == 0);
    printf("Counting: %f ", (double)(t5 - t4) / CLOCKS_PER_SEC);
    REQUIRE(memcmp(CountingDest, Bubble, SIZE*sizeof(int)) == 0);
    printf("Radix base 2: %f ", (double)(t6 - t5) / CLOCKS_PER_SEC);    
    REQUIRE(memcmp(Radix1, Bubble, SIZE*sizeof(int)) == 0);    
    printf("Radix base 10: %f ", (double)(t7 - t6) / CLOCKS_PER_SEC);    
    REQUIRE(memcmp(Radix2, Bubble, SIZE*sizeof(int)) == 0);
    printf("Merge: %f ", (double)(t8 - t7) / CLOCKS_PER_SEC);
    REQUIRE(memcmp(MergeDest, Bubble, SIZE*sizeof(int)) == 0);
    printf("Heap: %f ", (double)(t9 - t8) / CLOCKS_PER_SEC);
    REQUIRE(memcmp(Heap, Bubble, SIZE*sizeof(int)) == 0);
    printf("Quick: %f ", (double)(t10 - t9) / CLOCKS_PER_SEC);
    REQUIRE(memcmp(Quick, Bubble, SIZE*sizeof(int)) == 0);

    return 0;
} 