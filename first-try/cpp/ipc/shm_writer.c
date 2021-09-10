#include <stdio.h> /* sprintf */
#include <string.h>  /* strlen */
#include <fcntl.h> /* O_CREAT, ORDWR*/ 
#include <unistd.h> /* ftruncate */
#include <sys/mman.h> /* shm_open, mmap, PROT_WRITE, MAP_SHARED */

#define SIZE 100

int main()
{
    int shm_fd = shm_open("shm", O_CREAT | O_RDWR, 0666);
    void* shm_ptr = NULL;
    char* str = "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z";

    if (shm_fd == -1)
    {
        return 1;
    }

    ftruncate(shm_fd, SIZE);
    
    shm_ptr = mmap((void*)0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    sprintf(shm_ptr, "%s", str);

    shm_ptr += strlen(str);

    sprintf(shm_ptr, "%s", str);

    return 0;
}