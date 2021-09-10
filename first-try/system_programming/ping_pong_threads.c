#include <sys/sem.h> /* all sem funcs and macros */
#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */
#include <pthread.h>

#define KEY_FILE "/tmp/xyz"
#define N_THREADS 2

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
};

struct sembuf p1 = {0, -1, SEM_UNDO};
struct sembuf v1 = {0, +1, SEM_UNDO};
struct sembuf p2 = {1, -1, SEM_UNDO};
struct sembuf v2 = {1, +1, SEM_UNDO};

void *PingThread(void *id)
{
    int i = 0;

    for (i = 0; i < 5; ++i)
    {
        semop(*(int*)id, &p1, 1);
        printf("ping\n");
        sleep(1);
        semop(*(int*)id, &v2, 1);
    };

    return NULL;
}

void *PongThread(void *id)
{
    int i = 0;

    for (i = 0; i < 5; ++i)
        {
            semop(*(int*)id, &p2, 1);
            printf("pong\n");
            sleep(1);
            semop(*(int*)id, &v1, 1);
        };

    return NULL;
}

int main()
{
    key_t key = -1;
    int id = 0;
    union semun u = {0};
    pthread_t threads[N_THREADS];

    FILE *new_file = fopen(KEY_FILE, "a");
    if (new_file == NULL)
    {
        printf("file error\n");
        return 1;
    }
    fclose(new_file);

    key = ftok(KEY_FILE, 'f');
    if (key == -1)
    {
        printf("key error\n");
        return 1;
    }

    id = semget(key, 2, 0666 | IPC_CREAT);
    if (id == -1)
    {
        printf("id error\n");
        return 1;
    }

    u.val = 1;
    semctl(id, 0, SETVAL, u);
    u.val = 0;
    semctl(id, 1, SETVAL, u);

    pthread_create(&threads[0], NULL, PingThread, &id);
    pthread_create(&threads[1], NULL, PongThread, &id);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    semctl(id, 0, IPC_RMID, u);

    return 0;
}