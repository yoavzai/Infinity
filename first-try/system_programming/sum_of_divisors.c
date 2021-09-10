/* with 30000 threads in parallel, calculate the sum of all divisor of a large number
    then with one thread
    then with one thread and optimiztaion */

/*
Threads = 1, Number = 268435455, Sum of divisors = 462274560
real    0m2.202s

Threads = 2, Number = 268435455, Sum of divisors = 462274560
real    0m1.114s

Threads = 10, Number = 268435455, Sum of divisors = 462274560
real    0m0.591s

Threads = 20, Number = 268435455, Sum of divisors = 462274560
real    0m0.582s

Threads = 30, Number = 268435455, Sum of divisors = 462274560
real    0m0.577s

Threads = 40, Number = 268435455, Sum of divisors = 462274560
real    0m0.590s

Threads = 50, Number = 268435455, Sum of divisors = 462274560
real    0m0.584s

Threads = 100, Number = 268435455, Sum of divisors = 462274560
real    0m0.580s

Threads = 1000, Number = 268435455, Sum of divisors = 462274560
real    0m0.596s

Threads = 10000, Number = 268435455, Sum of divisors = 462274560
real    0m0.826s

Threads = 32000, Number = 268435455, Sum of divisors = 462274560
real    0m1.002s

Threads = 1, Number = 5000000000, Sum of divisors = 12487792713
real    0m58.357s

Threads = 4, Number = 5000000000, Sum of divisors = 12487792713
real    0m28.226s

Threads = 20, Number = 5000000000, Sum of divisors = 12487792713
real    0m23.790s

Threads = 30, Number = 5000000000, Sum of divisors = 12487792713
real    0m24.100s
 
Threads = 10000, Number = 5000000000, Sum of divisors = 12487792713
real    0m24.610s
*/

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h> /* getpid */

#define N_THREADS 10

#define NUM 5000000000

size_t partial_sums_arr[N_THREADS];
size_t n_iter_per_thread;
size_t reminder;
size_t big_num;

void* Routine(void* sum_addr)
{
    size_t i = ((size_t)sum_addr - (size_t)partial_sums_arr) / sizeof(size_t);
    size_t starting_from = i * n_iter_per_thread + 1;
    size_t ending_at = starting_from + n_iter_per_thread;
    while (starting_from < ending_at)
    {
        if (big_num % starting_from == 0)
        {
            *((size_t*)sum_addr) += starting_from;
        }

        starting_from++;
    }

    return NULL;
}

void* LastRoutine(void* sum_addr)
{
    size_t i = (((size_t)sum_addr - (size_t)partial_sums_arr) / sizeof(size_t));
    size_t starting_from = i * n_iter_per_thread + 1;
    size_t ending_at = starting_from + n_iter_per_thread + reminder;
    

    while (starting_from < ending_at)
    {
        if (big_num % starting_from == 0)
        {
            *((size_t*)sum_addr) += starting_from;
        }

        starting_from++;
    }

    return NULL;
}

size_t SumArr()
{
    size_t i = 0;
    size_t sum = 0;

    for (i = 0; i < N_THREADS; ++i)
    {
        sum += partial_sums_arr[i];
    }

    return sum;
}

int main()
{
    size_t i = 0;
    pthread_t threads[N_THREADS];
    size_t sum;

    big_num = NUM;
 
    n_iter_per_thread = big_num / N_THREADS;
    reminder = big_num % N_THREADS;

    for (i = 0; i < N_THREADS - 1; ++i)
    {
        pthread_create(&threads[i], NULL, Routine, &partial_sums_arr[i]);
    }

    pthread_create(&threads[i], NULL, LastRoutine, &partial_sums_arr[i]);

    for (i = 0; i < N_THREADS; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    sum = SumArr();

    printf("Threads = %d, Number = %lu, Sum of divisors = %lu",N_THREADS, big_num, sum);

    return 0;
}