#include <sys/sem.h> /* all sem funcs and macros */
#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */

#define KEY_FILE "/tmp/xyz"

struct sembuf p1 = {0, -1, SEM_UNDO};
struct sembuf v1 = {0, +1, SEM_UNDO};
struct sembuf p2 = {1, -1, SEM_UNDO};
struct sembuf v2 = {1, +1, SEM_UNDO};

int main()
{

    int i = 0;
    key_t key = -1;
    int id = 0;

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

    printf("key %d\n", key);
    printf("id %d\n", id);

    for (i = 0; i < 5; ++i)
    {
        semop(id, &p2, 1);
        printf("pong\n");
        sleep(1);
        semop(id, &v1, 1);
    };
    
    return 0;
}