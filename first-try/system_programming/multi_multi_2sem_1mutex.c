#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h> /* sleep */

#include "circ_buff.h"

#define CYCLES 2000
#define N_THREADS 4
#define CAPACITY 3

int con_counter = 1;
int pro_counter = 1;
int arr[CAPACITY];

pthread_mutex_t mutex;
sem_t read_sem;
sem_t write_sem;

void* ConRoutine(void* unused)
{
    int pro_serial = 0;
    int my_serial = 0;
    int i = 0;

    pthread_mutex_lock(&mutex);
    my_serial = con_counter;
    con_counter++;
    pthread_mutex_unlock(&mutex);

    while (i < CYCLES)
    {
        sem_wait(&read_sem);
        pthread_mutex_lock(&mutex);

        pro_serial = CBRead();
        printf("        con %d read pro %d\n", my_serial, pro_serial);

        sem_post(&write_sem);

        pthread_mutex_unlock(&mutex);

        ++i;

        sleep(0);
    }

    return NULL;
}

void* ProRoutine(void* queue)
{
    int my_serial = 0;
    int i = 0;

    pthread_mutex_lock(&mutex);
    my_serial = pro_counter;
    pro_counter++;
    pthread_mutex_unlock(&mutex);

    while (i < CYCLES)
    {
        sem_wait(&write_sem);
        pthread_mutex_lock(&mutex);

        CBWrite(my_serial);
        printf("pro %d wrote\n", my_serial);

        sem_post(&read_sem);

        pthread_mutex_unlock(&mutex);

        ++i;

        sleep(0);
    }

    return NULL;
}

int main()
{
    int i = 0;
    pthread_t con[N_THREADS] = {0};
    pthread_t pro[N_THREADS] = {0};

    CBCreate(arr, CAPACITY);
    pthread_mutex_init(&mutex, NULL);
    sem_init(&read_sem, 0, 0);
    sem_init(&write_sem, 0, CAPACITY);

    for (i = 0; i < N_THREADS; ++i)
    {
        if (pthread_create(&pro[i], NULL, ProRoutine, NULL) != 0)
        {
            return 1;
        }
        
        if (pthread_create(&con[i], NULL, ConRoutine, NULL) != 0)
        {
            return 1;
        }
    }

    for (i = 0; i < N_THREADS; ++i)
    {
        pthread_join(pro[i], NULL);
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&read_sem);
    sem_destroy(&write_sem);

    return 0;
}