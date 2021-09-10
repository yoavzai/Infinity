#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int fd = 0;
    int i = 0;
    char buff[5];

    mkfifo("buffer", 0666);

    for (i = 0; i < 5; ++i)
    {
        fd = open("buffer", O_RDONLY);
        read(fd, buff, 4);
        printf("%s\n", buff);
        close(fd);
        fd = open("buffer", O_WRONLY);
        write(fd, "Pong", 4);
        close(fd);
        sleep(1);
    }
    
    return 0;
}