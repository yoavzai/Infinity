#include <sys/types.h> /* pid_t */
#include <signal.h> /* kill */
#include <unistd.h> /* getpid */
#include <stdio.h> /* printf */

volatile sig_atomic_t child_waiting = 1;

void ChildSigHandler(int signum)
{
    write(1, "Pong\n", 5);
    signal(signum, ChildSigHandler);
    child_waiting = 0;
}

int main()
{
    int i = 0;

    signal(SIGUSR1, ChildSigHandler);

    for (i = 0; i < 5; ++i)
    {
        kill(getppid(), SIGUSR2);
        
        while (child_waiting)
        {
            ;
        }
        sleep(1);
        child_waiting = 1;    
    }

    kill(getppid(), SIGUSR1);

    return 0;
}