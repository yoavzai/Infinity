#include <sys/types.h> /* pid_t */
#include <unistd.h> /* getpid */
#include <stdio.h> /* printf */
#include <stdlib.h> /* getenv, atoi */
#include <semaphore.h> /* semphores */
#include <fcntl.h> /* O_ flags for semaphores */
#include <sys/stat.h> /* modes for semaphores */
#include <signal.h> /* sig_atomic_t, sigaction, kill */
#include <string.h> /* memset */

#include "scheduler.h"

sem_t *thread_ready;
sem_t *wd_ready;
sem_t *all_ready;
pid_t user_app_pid;
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
    kill(user_app_pid, SIGUSR1);

    counter++;

    return 0;
}

int ReviveFunc(void *argv)
{
    /* printf("WD counter = %d\n", counter); */

    if (counter >= atoi(getenv("max_intervals")))
    {
        pid_t child_pid = fork();

        if (child_pid == 0)
        {
            execv(*(char**)argv, argv);
        }
        
        counter = 0;
        user_app_pid = child_pid;

        sem_post(wd_ready);
        sem_wait(thread_ready);
    }

    return 0;
}

void SetSemaphores()
{
    all_ready = sem_open("all_ready", O_CREAT, 0666, 0);
    wd_ready = sem_open("wd_ready", O_CREAT, 0666, 0);
    thread_ready = sem_open("thread_ready", O_CREAT, 0666, 0);
}

int main(int argc, char* argv[])
{
    struct sigaction ping_arrived;
    struct sigaction dnr;

    user_app_pid = getppid();

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

    SetSemaphores();

    sem_post(wd_ready);
    sem_wait(thread_ready);

    TSRun(sched);
    TSDestroy(sched);

    return 0;
}