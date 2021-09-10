#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "priority_q.h"
#include "sorted_list.h"

struct pq
{
    srlist_t* srlist;
};

pq_t* PQCreate(comp_func_t comp_priority, const void* param)
{
    pq_t* new_pq = malloc(sizeof(pq_t));

    if (!new_pq)
    {
        return NULL;
    }

    new_pq->srlist = SortedListCreate(comp_priority, param);

    if (!new_pq->srlist)
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
    SortedListDestroy(pq->srlist);
    free(pq);
    pq = NULL;
}

int PQEnqueue(pq_t* pq, void* data)
{
    assert(pq);

    return (SortedListGetData(SortedListInsert(pq->srlist, data)) == NULL);
}

void* PQDequeue(pq_t* pq)
{
    assert(pq);

    return SortedListPopFront(pq->srlist);
}

void* PQPeek(const pq_t* pq)
{
    assert(pq);

    return SortedListGetData(SortedListBegin(pq->srlist));
}

int PQIsEmpty(const pq_t* pq)
{
    assert(pq);

    return SortedListIsEmpty(pq->srlist);
}

size_t PQSize(const pq_t* pq)
{
    assert(pq);

    return SortedListSize(pq->srlist);
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
    void* return_data = NULL;
    sorted_list_iter_t iter = {0};
    assert(pq);

    iter = SortedListFindIf(SortedListBegin(pq->srlist),
                            SortedListEnd(pq->srlist),
                            match_func, data);


    return_data = SortedListGetData(iter);
    SortedListRemove(iter);

    return return_data; 
}
