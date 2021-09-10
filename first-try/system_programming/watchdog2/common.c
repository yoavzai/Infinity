#include <sys/types.h> /* pid_t */
#include <unistd.h> /* getppid */
#include <stdio.h> /* printf */
#include <stdlib.h> /* getenv, atoi */
#include <semaphore.h> /* semphores */
#include <fcntl.h> /* O_ flags for semaphores */
#include <sys/stat.h> /* modes for semaphores */
#include <signal.h> /* sig_atomic_t, sigaction, kill */
#include <string.h> /* memset, strcmp */

#include "scheduler.h"
#include "common.h"
#include "wd.h"

#define NOT_USED(x) (void)x

static int SecondProcNotResponding();
static void PingArrivedHandler(int signum);
static void DNRHandler(int signum);
static int StopSched(void *sched);
static int Ping(void *param);
static int ReviveProc(void *param);

sem_t *thread_ready = NULL;
sem_t *wd_ready;
sem_t *all_ready;
pid_t ping_to;
sig_atomic_t counter = 0;
sig_atomic_t stop_sched = 0;

/******* Handlers Stuff *******/

void InitHandlers()
{
    struct sigaction ping_arrived;
    struct sigaction dnr;

/* setting up ping_arrived handler */
    memset(&ping_arrived, 0, sizeof(struct sigaction));
	sigemptyset(&ping_arrived.sa_mask);

	ping_arrived.sa_handler = PingArrivedHandler;
	ping_arrived.sa_flags = 0;

    sigaction(SIGUSR1, &ping_arrived, NULL);

/* setting up dnr handler */
    memset(&dnr, 0, sizeof(struct sigaction));
	sigemptyset(&dnr.sa_mask);

	dnr.sa_handler = DNRHandler;
	dnr.sa_flags = 0;

    sigaction(SIGUSR2, &dnr, NULL);

/* TODO - set SIGCHLD handler to reap zombie kids */

}

static void PingArrivedHandler(int signum)
{
    NOT_USED(signum);

    counter = 0;
}

static void DNRHandler(int signum)
{
    NOT_USED(signum);

    stop_sched = 1;
}

/******* Scheduler Stuff ********/

scheduler_t *InitScheduler(proc_data_t *second_proc_data)
{
    scheduler_t *sched = TSCreate();

    TSAdd(sched, atoi(getenv("interval")), Ping, NULL);
    TSAdd(sched, atoi(getenv("interval")), ReviveProc, second_proc_data);
    TSAdd(sched, atoi(getenv("interval")), StopSched, sched);

    return sched;
}

static int StopSched(void *sched)
{
    if (stop_sched)
    {
        TSStop(sched);

        return 1;
    }

    return 0;
}

static int Ping(void *param)
{
    NOT_USED(param);

    kill(ping_to, SIGUSR1);

    counter++;

    return 0;
}

static int ReviveProc(void *param)
{
    proc_data_t *second_proc_data = (proc_data_t*)param;

    if (SecondProcNotResponding())
    {
        ping_to = CreateProc(second_proc_data);
        counter = 0;
    
        if (strcmp(second_proc_data->path, WD_PATH) == 0) /* reviving WD */
        {
            sem_post(thread_ready);
            sem_wait(wd_ready);
        }

        else /* reviving user_app */
        {
            sem_post(wd_ready);
            sem_wait(thread_ready);
        }
    }

    return 0;
}

static int SecondProcNotResponding()
{
    return counter >= atoi(getenv("max_intervals"));
}

/************ Other Stuff **************/

pid_t CreateProc(proc_data_t *proc)
{
    pid_t child_pid = fork();

    if (child_pid == 0)
    {
        execv(proc->path, proc->argv);
    }

    return child_pid;
}

void SetSemaphores()
{
    all_ready = sem_open("/all_ready", O_CREAT, 0666, 0);
    wd_ready = sem_open("/wd_ready", O_CREAT, 0666, 0);
    thread_ready = sem_open("/thread_ready", O_CREAT, 0666, 0);
}

void CleanSemaphores()
{
    sem_close(wd_ready);
    sem_close(all_ready);
    sem_close(thread_ready);
    sem_unlink("/thread_ready");
    sem_unlink("/all_ready");
    sem_unlink("/wd_ready");
}