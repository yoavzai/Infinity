#include <pthread.h>
#include <semaphore.h>
#include <stdio.h> /* printf, puts */

#define CYCLES 10
#define N_CONSUMERS 10

pthread_cond_t cv;
pthread_mutex_t mutex;
sem_t sem;
int counter;
int messege;

void* ProThread(void* unused)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < CYCLES; ++i)
    {
        messege = i;

        for (j = 0; j < N_CONSUMERS; ++j)
        {
            sem_post(&sem);
        }

        pthread_mutex_lock(&mutex);

        if (counter == N_CONSUMERS)
        {
            counter = 0;

            pthread_cond_broadcast(&cv);
        }

        else
        {
            counter++;

            pthread_cond_wait(&cv, &mutex);
        }

        pthread_mutex_unlock(&mutex);
        puts("");
    }

    return NULL;
}

void* ConThread(void* unused)
{
    int i = 0;

    for (i = 0; i < CYCLES; ++i)
    {
        sem_wait(&sem);

        printf("%d", messege);

        pthread_mutex_lock(&mutex);

        if (counter == N_CONSUMERS)
        {
            counter = 0;

            pthread_cond_broadcast(&cv);
        }

        else
        {
            counter++;

            pthread_cond_wait(&cv, &mutex);
        }

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void Init()
{
    pthread_cond_init(&cv, NULL);
    pthread_mutex_init(&mutex, NULL);
    sem_init(&sem, 0, 0);
}

void Destroy()
{
    pthread_cond_destroy(&cv);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem);
}

int main()
{
    pthread_t threads[N_CONSUMERS + 1];
    int i = 0;

    Init();

    for (i = 0; i < N_CONSUMERS; ++i)
    {
        pthread_create(&threads[i], NULL, ConThread, NULL);
    }

    pthread_create(&threads[i], NULL, ProThread, NULL);

    for (i = 0; i < N_CONSUMERS + 1; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    Destroy();

    return 0;
}