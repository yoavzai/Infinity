#include <time.h> /*time()*/
#include <stdlib.h> /* malloc, free */

#include "uid.h"
#include "task.h"
#include "scheduler.h" /* op_func_t */

task_t* TaskCreate(size_t interval, op_func_t operation, void* param)
{
    task_t* new_task = malloc(sizeof(task_t));

    if (!new_task)
    {
        return NULL;
    }

    new_task->uid = UIDCreate();
    new_task->interval = interval;
    new_task->next_run = time(NULL) + interval;
    new_task->operation = operation;
    new_task->param = param;

    return new_task;
}

void TaskDestroy(task_t* task)
{
    free(task);
}

int TaskCompare(const void* data1, const void* data2, const void* param)
{
    param = param;

    /* for priority_q */
    /*return (((task_t*)data1)->next_run < ((task_t*)data2)->next_run);*/

    /* for pq_heap */
    return (((task_t*)data1)->next_run <= ((task_t*)data2)->next_run);

}

void TaskUpdate(task_t* task)
{
    task->next_run = time(NULL) + task->interval;
}

int TaskMatch(const void* data, const void* param)
{
    return !UIDIsSame(((task_t*)data)->uid, *(ilrd_uid_t*)param);
}

ilrd_uid_t TaskGetUID(task_t* task)
{
    return task->uid;
}

size_t TaskNextRun(task_t* task)
{
    return task->next_run;
}

int TaskOperate(task_t* task)
{
    return task->operation(task->param); 
}