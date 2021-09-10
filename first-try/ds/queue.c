#include <stdlib.h> /* malloc, free */
#include <stdio.h> /* printf */

#include "SList.h"
#include "queue.h"

#ifndef NDEBUG
void PrintList(slist_node_t* head)
{
    while (head != NULL)
    {
        printf("%d ", *(int*)(head->data));
        head = head->next;
    }
    puts("");  
}
#endif

struct queue
{
    slist_node_t* first;
    slist_node_t* last;    
};

queue_t* QCreate()
{
    queue_t* new_queue = malloc(sizeof(queue_t));

    if (new_queue == NULL)
    {
        return NULL;
    }
    
    new_queue->first = SListCreateNode(NULL, NULL);

    if (new_queue->first == NULL)
    {
        free(new_queue);
        new_queue = NULL;
        return NULL;
    }
    
    new_queue->last = new_queue->first;

    return new_queue;
}

void QDestroy(queue_t* queue)
{
    SListFreeAll(queue->first);
    free(queue);
    queue = NULL;
}

void QDequeue(queue_t* queue)
{
    if (queue->first->next == queue->last)
    {
        queue->last = queue->first;
    }

    SListRemoveAfter(queue->first);
}

int QEnqueue(queue_t* queue, void* data)
{
    slist_node_t* new_node = SListCreateNode(data, NULL);

    if (new_node == NULL)
    {
        return 1;
    }
    
    queue->last = SListInsertAfter(queue->last, new_node);

    return 0;
}

void* QPeek(const queue_t* queue)
{
    if (queue->first->next == NULL)
    {
        return NULL;
    }

    return queue->first->next->data;
}

size_t QSize(const queue_t* queue)
{
    return SListCount(queue->first->next);
}

int QIsEmpty(const queue_t* queue)
{
    return queue->first == queue->last;
}

void QAppend(queue_t* dest, queue_t* src)
{
	if (QSize(src) == 0)
	{		
		return;
	}
	
    dest->last->next = src->first->next;
	dest->last = src->last;
    src->first->next = NULL;
    src->last = src->first;   
}




























