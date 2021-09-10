#include <pthread.h>
#include <stdio.h>

#define ARR_SIZE 10
#define CYCLES 5

enum whos_turn {PRO, CON};

int arr[ARR_SIZE];

enum whos_turn turn = PRO; 

void* ConRoutine(void* unused)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < CYCLES; ++i)
    {
        while (turn == PRO)
        {
            ;
        }

        for (j = 0; j < ARR_SIZE; ++j)
        {
            printf("%d", arr[j]);
        }

        puts("");
        turn = PRO;
    }

    return NULL;
}

void* ProRoutine(void* unused)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < CYCLES; ++i)
    {
        while (turn == CON)
        {
            ;
        }

        for (j = 0; j < ARR_SIZE; ++j)
        {
            arr[j] = i;
        }

        turn = CON;
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