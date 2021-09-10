#ifndef _COMMON_
#define _COMMON_

extern sem_t *thread_ready;
extern sem_t *wd_ready;
extern sem_t *all_ready;
extern pid_t ping_to;

typedef struct
{
    char **argv;
    char  *path;

} proc_data_t;

void InitHandlers();
scheduler_t *InitScheduler(proc_data_t *second_proc_data);
pid_t CreateProc(proc_data_t *proc);
void SetSemaphores();
void CleanSemaphores();

#endif