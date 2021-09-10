#include <stdio.h> /* printf */
#include <time.h> /* time() */

#include "scheduler.h"
#include "test_functions.h"

#define RESET "\033[0m"

int Tv(void* param);
int Dog(void* param);
int Food(void* param);
int Sport(void* param);
int Stop(void* param);

static size_t start_time;

typedef struct tasks
{
    scheduler_t* scheduler;
    ilrd_uid_t tasks[4];
}tasks_t;

int Dog(void* param)
{
    static int counter = 1; 
    printf("%lu seconds - Dog\n", time(NULL) - start_time);

    if (counter == 4)
    {
        ((tasks_t*)param)->tasks[2] = TSAdd(((tasks_t*)param)->scheduler, 2, 
                                            &Stop, param);
        ((tasks_t*)param)->tasks[3] = TSAdd(((tasks_t*)param)->scheduler, 1, 
                                            &Tv, param);
        return 1;
    }

    counter++;
    return 0;
}

int Food(void* param)
{
    static int counter = 1;
    printf("%lu seconds - Food\n", time(NULL) - start_time);

    if (counter == 4)
    {
        TSClear(((tasks_t*)param)->scheduler);
        return 1;
    }

    counter++;
    return 0;
}

int Tv(void* param)
{
    static int counter = 1;
    param = param; 
    printf("%lu seconds - Tv\n", time(NULL) - start_time);

    if (counter == 4)
    {
        return 1;
    }

    counter++;
    return 0;
}

int Sport(void* param)
{
    static int counter = 1;
    param = param;

    printf("%lu seconds - Sport\n", time(NULL) - start_time);

    counter++;
    return 0;
}

int Stop(void* param)
{
    TSStop(((tasks_t*)param)->scheduler);
    return 1;
}

/********************************************************/


int main()
{
    int status = 0;
    tasks_t my_tasks;
    my_tasks.scheduler = TSCreate();
    VerifyInt(TSIsEmpty(my_tasks.scheduler), 1, "Create, IsEmpty");
    my_tasks.tasks[0] = TSAdd(my_tasks.scheduler, 2, &Dog, &my_tasks);
    my_tasks.tasks[1] = TSAdd(my_tasks.scheduler, 4, &Food, &my_tasks);
    VerifySizeT(TSSize(my_tasks.scheduler), 2, "Create, Add, Size");
    VerifyInt(TSIsEmpty(my_tasks.scheduler), 0, "IsEmpty");
    printf(RESET"------------------------\n");

    start_time = time(NULL);
    status = TSRun(my_tasks.scheduler);
    printf("Stoped at %lu seconds, status - %d\n", time(NULL) - start_time, status);
    printf(RESET"------------------------\n");
    VerifyInt(status, 1, "Stop");

    my_tasks.tasks[0] = TSAdd(my_tasks.scheduler, 3, &Sport, &my_tasks);
    VerifySizeT(TSSize(my_tasks.scheduler), 3, "Add, Remove");
    printf(RESET"------------------------\n");

    status = TSRun(my_tasks.scheduler);
    printf("Stoped at %lu seconds, status - %d\n", time(NULL) - start_time, status);
    printf(RESET"------------------------\n");
    VerifyInt(status, 0, "Clear, Run");
    VerifyInt(TSIsEmpty(my_tasks.scheduler), 1, "Clear");

    TSDestroy(my_tasks.scheduler);
    
    return 0;
}

/* expected output:

Create, IsEmpty SUCCESS
Create, Add, Size SUCCESS
IsEmpty SUCCESS
------------------------
2 seconds - Dog
4 seconds - Dog
4 seconds - Food
6 seconds - Dog
8 seconds - Dog
8 seconds - Food
9 seconds - Tv
10 seconds - Tv
Stoped at 10 seconds, status - 1
------------------------
Stop SUCCESS
Add, Remove SUCCESS
------------------------
11 seconds - Tv
12 seconds - Tv
12 seconds - Food
13 seconds - Sport
16 seconds - Sport
16 seconds - Food
Stoped at 16 seconds, status - 0
------------------------
Clear, Run SUCCESS
Clear SUCCESS

*/