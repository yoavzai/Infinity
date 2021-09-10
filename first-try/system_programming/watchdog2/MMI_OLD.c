#include <pthread.h> /* pthread_create */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* setenv */
#include <stdio.h> /* sprintf */
#include <semaphore.h> /* semphores */
#include <fcntl.h> /* O_ flags for semaphores */
#include <sys/stat.h> /* modes for semaphores */
#include <signal.h> /* sig_atomic_t sigaction */
#include <string.h> /* memset */

#include "MMI.h"
#include "scheduler.h"

sem_t *thread_ready;
sem_t *wd_ready;
sem_t *all_ready;
pid_t wd_pid;
pthread_t wd_thread;
sig_atomic_t counter = 0;
sig_atomic_t stop_sched = 0;

void PingArrivedHandler(int signum)
{
    counter = 0;
}

void DNRHandler(int signum)
{
    stop_sched = 1;
}

int StopSched(void *sched)
{
    if (stop_sched)
    {
        TSStop(sched);

        return 1;
    }

    return 0;
}

int PingFunc(void *param)
{
    kill(wd_pid, SIGUSR1);

    counter++;

    return 0;
}

int ReviveFunc(void *argv)
{
    /* printf("Thread counter = %d\n", counter); */

    if (counter >= atoi(getenv("max_intervals")))
    {
        pid_t child_pid = fork();

        if (child_pid == 0)
        {
            execv("./WD.out", argv);
        }
        
        counter = 0;
        wd_pid = child_pid;

        sem_wait(wd_ready);
        sem_post(thread_ready);
    }

    return 0;
}

void SetSemaphores()
{
    all_ready = sem_open("all_ready", O_CREAT, 0666, 0);
    wd_ready = sem_open("wd_ready", O_CREAT, 0666, 0);
    thread_ready = sem_open("thread_ready", O_CREAT, 0666, 0);
}

void CleanSemaphores()
{
    sem_close(wd_ready);
    sem_close(all_ready);
    sem_close(thread_ready);
    sem_unlink("thread_ready");
    sem_unlink("all_ready");
    sem_unlink("wd_ready");
}

void SetEnvVariables(const size_t interval, size_t max_intervals)
{
    char interval_str[10];
    char max_intervals_str[10];

    sprintf(interval_str, "%lu", interval);
    sprintf(max_intervals_str, "%lu", max_intervals);
    setenv("interval", interval_str, 0);
    setenv("max_intervals", max_intervals_str, 0);
}

void CleanEnvVariables()
{
    unsetenv("interval");
    unsetenv("max_intervals");
    unsetenv("first_time");
}

void *ThreadFunc(void *argv)
{
    struct sigaction ping_arrived;
    struct sigaction dnr;

    if (getenv("first_time") == NULL)
    {
        setenv("first_time", "yes", 0);

        pid_t child_pid = fork();

        if (child_pid == 0)
        {
            execv("./WD.out", argv);
        }

        wd_pid = child_pid;
    }

    else
    {
        wd_pid = getppid();
    }
    
/* Init handlers */
    memset(&ping_arrived, 0, sizeof(struct sigaction));
	sigemptyset(&ping_arrived.sa_mask);

	ping_arrived.sa_handler = PingArrivedHandler;
	ping_arrived.sa_flags = 0;

    sigaction(SIGUSR1, &ping_arrived, NULL);

    memset(&dnr, 0, sizeof(struct sigaction));
	sigemptyset(&dnr.sa_mask);

	dnr.sa_handler = DNRHandler;
	dnr.sa_flags = 0;

    sigaction(SIGUSR2, &dnr, NULL);

/* sched init */
    scheduler_t* sched = TSCreate();
    TSAdd(sched, atoi(getenv("interval")), PingFunc, NULL);
    TSAdd(sched, atoi(getenv("interval")), ReviveFunc, argv);
    TSAdd(sched, atoi(getenv("interval")), StopSched, sched);

    sem_wait(wd_ready);
    sem_post(thread_ready);
    sem_post(all_ready);

    TSRun(sched);
    TSDestroy(sched);
    
    return NULL;
}

void MMI(char** argv, const size_t interval, size_t max_intervals)
{
    SetEnvVariables(interval, max_intervals);
    SetSemaphores();

    pthread_create(&wd_thread, NULL, ThreadFunc, argv);

    sem_wait(all_ready);
}

void DNR()
{
    raise(SIGUSR2);
    kill(wd_pid, SIGUSR2);
    pthread_join(wd_thread, NULL);
    CleanSemaphores();
    CleanEnvVariables();
    
}