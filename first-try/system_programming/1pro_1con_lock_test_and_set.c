#include <pthread.h>
#include <stdio.h>
#include <unistd.h> /* sleep */

#define ARR_SIZE 10
#define CYCLES 5

int arr[ARR_SIZE];

int lock = 0; 

void* ConRoutine(void* unused)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < CYCLES; ++i)
    {
        while (__sync_lock_test_and_set(&lock, 1))
        {
            ;
        }

        for (j = 0; j < ARR_SIZE; ++j)
        {
            printf("%d", arr[j]);
        }

        puts("");

        __sync_lock_release(&lock);

        sleep(0);       
    }

    return NULL;
}

void* ProRoutine(void* unused)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < CYCLES; ++i)
    {
        while (__sync_lock_test_and_set(&lock, 1))
        {
            ;
        }

        for (j = 0; j < ARR_SIZE; ++j)
        {
            arr[j] = i;
        }

        __sync_lock_release(&lock);

        sleep(0);
    }

    return NULL;
}

int main()
{
    pthread_t con = 0;
    pthread_t pro = 0;

    if (pthread_create(&pro, NULL, ProRoutine, NULL) != 0)
    {
        return 1;
    }
    
    if (pthread_create(&con, NULL, ConRoutine, NULL) != 0)
    {
        return 1;
    }

    pthread_join(pro, NULL);
    pthread_join(con, NULL);

    return 0;
}