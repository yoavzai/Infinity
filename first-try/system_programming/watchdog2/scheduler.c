#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <time.h> /*time()*/


#include "priority_q.h"
#include "uid.h"
#include "task.h"
#include "scheduler.h"

struct scheduler
{
    int status;
    pq_t* pq;
};

static int compare(const void* data1, const void* data2, const void* param)
{
    return TaskCompare(data1, data2, param);
}

static int match(const void* data, const void* param)
{
    return TaskMatch(data, param);
}

/****************************************************************/

scheduler_t* TSCreate()
{
    scheduler_t* new = malloc(sizeof(scheduler_t));

    if (!new)
    {
        return NULL;
    }

    new->status = 0;
    new->pq = PQCreate(&compare, NULL);

    if (!new->pq)
    {
        free(new);
        new = NULL;
        return NULL;
    }

    return new;
}

void TSDestroy(scheduler_t* scheduler)
{
    TSClear(scheduler);
    PQDestroy(scheduler->pq);
    free(scheduler);
    scheduler = NULL;
}

int TSIsEmpty(const scheduler_t* scheduler)
{
    return PQIsEmpty(scheduler->pq);
}

size_t TSSize(const scheduler_t* scheduler)
{
    return PQSize(scheduler->pq);
}

ilrd_uid_t TSAdd(scheduler_t* scheduler, size_t interval, 
	             op_func_t operation, void* param)
{
    task_t* new_task = TaskCreate(interval, operation, param);

    if (!new_task)
    {
        return bad_uid;
    }

    if (PQEnqueue(scheduler->pq, new_task))
    {
        TaskDestroy(new_task);
        new_task = NULL;
        return bad_uid;
    }

    return TaskGetUID(new_task);

}

int TSRemove(scheduler_t* scheduler, ilrd_uid_t task_uid)
{
    void* task_to_erase = NULL;

    assert (scheduler);
    task_to_erase = PQErase(scheduler->pq, &match, &task_uid);

    if (task_to_erase == NULL)
    {
        return 1;
    }

    TaskDestroy(task_to_erase);
    task_to_erase = NULL;
    
    return 0;
}


void TSClear(scheduler_t* scheduler)
{
    while (!TSIsEmpty(scheduler))
    {
        TaskDestroy((PQDequeue(scheduler->pq)));
    }
}

int TSRun(scheduler_t* scheduler)
{
    task_t* cur_task = NULL;
    scheduler->status = 0;

    while (!TSIsEmpty(scheduler) && !scheduler->status)
    {
        size_t time_left = TaskNextRun(PQPeek(scheduler->pq)) - time(NULL);
        
        while (time_left > 0)
        {
            time_left = sleep(time_left);
        }

        cur_task = PQDequeue(scheduler->pq);
        TaskUpdate(cur_task);

        switch (TaskOperate(cur_task))
        {
            case 0:
                if (PQEnqueue(scheduler->pq, cur_task))
                {
                    TaskDestroy(cur_task);
                    scheduler->status = 2;
                }
                break;

            case 1:
                TaskDestroy(cur_task);
                break;

            case 2:
                TaskDestroy(cur_task);
                scheduler->status = 2;
        }
    }

    return scheduler->status;
}

void TSStop(scheduler_t* scheduler)
{
    scheduler->status = 1;
}
