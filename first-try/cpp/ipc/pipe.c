#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

enum Pipe {READ, WRITE};

int main()
{
    int i = 0;
    int pipefd1[2];
    int pipefd2[2];
    char buff[5];
    pid_t child = 0;

    if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1)
    {
        return 1;
    }

    if ((child = fork()) == -1)
    {
        return 1;
    }

    if (child == 0)
    {
        close(pipefd1[READ]);
        close(pipefd2[WRITE]);

        for (i = 0; i < 5; ++i)
        {
            write(pipefd1[WRITE], "Ping", 4);
            read(pipefd2[READ], buff, 4);
            printf("%s\n", buff);
        }
    }

    else
    {
        close(pipefd1[WRITE]);
        close(pipefd2[READ]);

        for (i = 0; i < 5; ++i)
        {
            read(pipefd1[READ], buff, 4);
            printf("%s\n", buff);
            write(pipefd2[WRITE], "Pong", 4);
        }    
    }
    
    return 0;
}