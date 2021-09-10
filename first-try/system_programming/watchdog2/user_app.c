#include <stdio.h> /* printf */
#include <stdlib.h> /* atoi */
#include <unistd.h> /* sleep */
#include <time.h> /* time */

#include "wd.h"

#define SLEEP 5

int main(int argc, char* argv[])
{
    time_t remaining_time = SLEEP;
    (void)argc;

    if (argc != 3)
    {
        printf("enter 2 args\n");
        return -1;
    }

    MMI((const char**)argv, 3, 3);

    printf("%s %s\n", argv[1], argv[2]);
    while (remaining_time)
    {
        printf("%ld\n", remaining_time);
        remaining_time = sleep(remaining_time);
    }  

    DNR();
    
    printf("Bye Bye!\n");

    return 0;
}