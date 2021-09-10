#include <stdio.h> /* printf */
#include <fcntl.h> /* O_RDONLY */
#include <sys/mman.h> /* shm_open, mmap, PROT_READ, MAP_SHARED */

#define SIZE 100

int main()
{
    int shm_fd = shm_open("shm", O_RDONLY, 0666);
    void* shm_ptr = NULL;

    if (shm_fd == -1)
    {
        return 1;
    }

    shm_ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

    printf("%s\n", (char*)shm_ptr);


    shm_unlink("shm");

    return 0;
}