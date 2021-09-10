#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "priority_q.h"
/*#include "sorted_list.h"*/
#include "heap.h"

struct pq
{
    heap_t* heap;
};

pq_t* PQCreate(comp_func_t comp_priority, const void* param)
{
    pq_t* new_pq = malloc(sizeof(pq_t));

    if (!new_pq)
    {
        return NULL;
    }

    new_pq->heap = HeapCreate(comp_priority);

    if (!new_pq->heap)
    {
        free(new_pq);
        new_pq = NULL;
        return NULL;
    }

    return new_pq;
}

void PQDestroy(pq_t* pq)
{
    assert(pq);
    HeapDestroy(pq->heap);
    free(pq);
    pq = NULL;
}

int PQEnqueue(pq_t* pq, void* data)
{
    assert(pq);

    return HeapPush(pq->heap, data);
}

void* PQDequeue(pq_t* pq)
{
    void* data = HeapPeek(pq->heap);

    HeapPop(pq->heap);

    return data;
}

void* PQPeek(const pq_t* pq)
{
    return HeapPeek(pq->heap);
}

int PQIsEmpty(const pq_t* pq)
{
    assert(pq);

    return HeapIsEmpty(pq->heap);
}

size_t PQSize(const pq_t* pq)
{
    assert(pq);

    return HeapSize(pq->heap);
}

void PQClear(pq_t* pq)
{
    assert(pq);

    while (!PQIsEmpty(pq))
    {
        PQDequeue(pq);
    }
}

void* PQErase(pq_t* pq, match_func_t match_func, const void* data)
{
    return HeapRemove(pq->heap, data, match_func);   
}
