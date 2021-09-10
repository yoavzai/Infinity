#include <semaphore.h> /* sempost, semwait */

#include "scheduler.h"
#include "common.h"

int main(int argc, char* argv[])
{
    scheduler_t* sched = {0};
    proc_data_t user_proc_data = {0};
    (void)argc;

    user_proc_data.path = argv[0];
    user_proc_data.argv = argv;

    sched = InitScheduler(&user_proc_data);
    ping_to = getppid();

    InitHandlers();
    SetSemaphores();

    sem_post(wd_ready);
    sem_wait(thread_ready);

    TSRun(sched);
    TSDestroy(sched);

    CleanSemaphores();

    return 0;
}