#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h> /* sleep */

#include "queue.h"

#define CYCLES 4
#define N_THREADS 4

int pro_serials[] = {1,2,3,4};

int con_counter = 1;
int pro_counter = 0;

pthread_mutex_t mutex;
sem_t sem;

void* ConRoutine(void* queue)
{
    void* pro_serial = NULL;
    int my_serial = 0;
    int i = 0;

    pthread_mutex_lock(&mutex);
    my_serial = con_counter;
    con_counter++;
    pthread_mutex_unlock(&mutex);

    while (i < CYCLES)
    {
        sem_wait(&sem);
        pthread_mutex_lock(&mutex);

        pro_serial = QPeek(queue);

        QDequeue(queue);
        pthread_mutex_unlock(&mutex);
        printf("con %d dequeued pro %d\n", my_serial, *((int*)pro_serial));

        ++i;

        sleep(0);
    }

    return NULL;
}

void* ProRoutine(void* queue)
{
    void* my_serial = NULL;
    int i = 0;

    pthread_mutex_lock(&mutex);
    my_serial = &pro_serials[pro_counter];
    pro_counter++;
    pthread_mutex_unlock(&mutex);

    while (i < CYCLES)
    {
        pthread_mutex_lock(&mutex);

        QEnqueue(queue, my_serial);

        pthread_mutex_unlock(&mutex);
        sem_post(&sem);

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
    queue_t* queue = NULL;

    queue = QCreate();
    pthread_mutex_init(&mutex, NULL);
    sem_init(&sem, 0, 0);

    for (i = 0; i < N_THREADS; ++i)
    {
        if (pthread_create(&pro[i], NULL, ProRoutine, queue) != 0)
        {
            return 1;
        }
        
        if (pthread_create(&con[i], NULL, ConRoutine, queue) != 0)
        {
            return 1;
        }
    }

    for (i = 0; i < N_THREADS; ++i)
    {
        pthread_join(pro[i], NULL);
        pthread_join(con[i], NULL);
    }

    QDestroy(queue);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem);

    return 0;
}