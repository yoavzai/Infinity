#include <sys/types.h> /* pid_t */
#include <signal.h> /* kill */
#include <unistd.h> /* fork getppid */
#include <stdio.h> /* printf */

volatile sig_atomic_t parent_waiting = 1;
volatile sig_atomic_t child_waiting = 1;

void ChildSigHandler(int signum)
{
    write(1, "Ping\n", 5);
    signal(signum, ChildSigHandler);
    child_waiting = 0;
}

void ParentSigHandler(int signum)
{
    write(1, "Pong\n", 5);
    signal(signum, ParentSigHandler);
    parent_waiting = 0;
}

int main()
{
    int i = 0;
    pid_t pid;

    signal(SIGUSR1, ChildSigHandler);
    signal(SIGUSR2, ParentSigHandler);

    pid = fork();

    if (pid == -1)
    {
        return -1;
    }

    for (i = 0; i < 5; ++i)
    {
        if (pid == 0)
        {
            while (child_waiting)
            {
                ;
            }
            sleep(1);
            child_waiting = 1;
            kill(getppid(), SIGUSR2);  
        }

        else
        {
            kill(pid, SIGUSR1);
            
            while (parent_waiting)
            {
                ;
            }
            sleep(1);
            parent_waiting = 1;
        }
    }

    return 0;
}