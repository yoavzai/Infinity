/* open 100k threads each set an index in an array of 100k to = idx + 1
  sleep for 10 sec and check that array is occupied */

#include <pthread.h>
#include <stdio.h>
#include <omp.h>

#define N_THREADS 100000

int arr[N_THREADS];

void* FillArr(void* addr)
{

    size_t i = ((size_t)addr - (size_t)arr) / sizeof(int);

    arr[i] = i + 1;

    return NULL;
}

void PrintArr()
{
    size_t i = 0;

    for (i = 0; i < N_THREADS; ++i)
    {
        printf("%d, ", arr[i]);
    }
}

int main()
{
    size_t i = 0;
    pthread_t cur_thread;

#pragma omp parallel for
    for (i = 0; i < N_THREADS; ++i)
    {
        FillArr(&arr[i]);
        /*pthread_create(&cur_thread, NULL, FillArr, &arr[i]);
        pthread_detach(cur_thread);*/
    }

    PrintArr();

    return 0;
}