#include <stdio.h> /* printf */
#include <unistd.h> /* fork, execlp */
#include <wait.h> /* waitpid */
#include <stdlib.h> /* system */

void ForkExec(char *p_name)
{
    int i = 0;

    for (i = 0; i < 5; ++i)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            return;
        }

        if (pid == 0)
        {
            if (execlp(p_name, p_name) == -1)
            {
                return;
            }
        }

        else
        {
            int status = 0;

            if (waitpid(pid, &status, 0) == -1)
            {
                return;
            }
        }
    }
}

void System(char *p_name)
{
    int i = 0;

    for (i = 0; i < 5; ++i)
    {
        if(system(p_name) == 0)
        {
            continue;
        }

        else
        {
            return;
        }
        
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Enter a program name\n");

        return -1;
    }

    ForkExec(argv[1]);
    System(argv[1]);

    return 0;
}