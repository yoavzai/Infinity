#include <sys/types.h> /* pid_t */
#include <signal.h> /* kill */
#include <unistd.h> /* fork getppid */
#include <stdio.h> /* printf */

volatile sig_atomic_t parent_waiting = 1;

void ParentSigHandler(int signum)
{
    write(1, "Ping\n", 5);
    signal(signum, ParentSigHandler);
    parent_waiting = 0;
}

void FinishSigHandler(int signum)
{
    (void)signum;
    parent_waiting = 0;
}

int main()
{
    char* path = "/home/yoavzai/yoav-zaidenberg/system_programming/pong1";
    int i = 0;
    pid_t pid;

    signal(SIGUSR2, ParentSigHandler);
    signal(SIGUSR1, FinishSigHandler);

    pid = fork();

    if (pid == -1)
    {
        return -1;
    }

    if (pid == 0)
    {
        if (execl(path, "pong1", (char*)NULL) == -1)
        {
            return -1;
        }  
    }

    for (i = 0; i < 5; ++i)
    {     
        while (parent_waiting)
        {
            ;
        }

        sleep(1);
        parent_waiting = 1;
        kill(pid, SIGUSR1);
    }

    while (parent_waiting)
        {
            ;
        }

    return 0;
}