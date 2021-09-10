#ifndef _TASK_H_
#define _TASK_H_

#include <stddef.h> /* size_t */

#include "scheduler.h" /* op_func_t */
#include "uid.h"

typedef struct task
{
	ilrd_uid_t uid;
	size_t interval;
	size_t next_run;
	op_func_t operation;
	void* param;
} task_t;

task_t* TaskCreate(size_t interval, op_func_t operation, void* param);
void TaskDestroy(task_t* task);
int TaskCompare(const void* data1, const void* data2, const void* param);
void TaskUpdate(task_t* task);
int TaskMatch(const void* data, const void* param);
ilrd_uid_t TaskGetUID(task_t* task);
size_t TaskNextRun(task_t* task);
int TaskOperate(task_t* task);

#endif
