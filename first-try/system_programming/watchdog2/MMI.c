#include <pthread.h> /* pthread_create, pthread_t */
#include <semaphore.h> /* semphores */
#include <signal.h> /* SIGUSR */
#include <stdio.h> /* sprintf */

#include "wd.h"
#include "scheduler.h"
#include "common.h"

static void *ThreadFunc(void *argv);
static int  IsFirstUseOfWD();
static void SetEnv(const size_t interval, size_t max_intervals);
static void CleanEnvVariables();

pthread_t wd_thread;

wd_status_t MMI(const char *uargv[], size_t interval, size_t max_intervals)
{
    SetEnv(interval, max_intervals);
    SetSemaphores();
    if (pthread_create(&wd_thread, NULL, ThreadFunc, uargv) != 0)
    {
        CleanSemaphores();
        CleanEnvVariables();

        return WD_FAILURE;
    }

    sem_wait(all_ready);

    return WD_SUCCESS;
}

void DNR()
{
    raise(SIGUSR2);
    kill(ping_to, SIGUSR2);
    printf("join %d\n", pthread_join(wd_thread, NULL));
    CleanSemaphores();
    CleanEnvVariables();
}

static void *ThreadFunc(void *argv)
{
    scheduler_t* sched = {0};
    proc_data_t wd_data = {0};

    wd_data.path = WD_PATH;
    wd_data.argv = (char**)argv;

    sched = InitScheduler(&wd_data);

    InitHandlers();

    if (IsFirstUseOfWD())
    {
        ping_to = CreateProc(&wd_data);
    }

    else
    {
        ping_to = getppid();
    }

    sem_post(thread_ready);
    sem_wait(wd_ready);
    sem_post(all_ready);

    TSRun(sched);
    TSDestroy(sched);
    
    return NULL;
}

static int IsFirstUseOfWD()
{
    if (getenv("first_time") == NULL)
    {
        setenv("first_time", "yes", 0);

        return 1;
    }

    return 0;
}

static void SetEnv(const size_t interval, size_t max_intervals)
{
    char interval_str[10];
    char max_intervals_str[10];

    sprintf(interval_str, "%lu", interval);
    sprintf(max_intervals_str, "%lu", max_intervals);
    setenv("interval", interval_str, 0);
    setenv("max_intervals", max_intervals_str, 0);
}

static void CleanEnvVariables()
{
    unsetenv("interval");
    unsetenv("max_intervals");
    unsetenv("first_time");
}