#include <stdlib.h> /* malloc, free */
#include <stdio.h> /* printf */

#include "heap.h"
#include "heapify.h"
#include "vector.h"

#define VECTOR(i) VectorGetItemAddress(heap->vector, i)
#define SIZE sizeof(void*)

struct heap
{
    vector_t* vector;
    cmp_func_t cmp_func;
};

/*************** Utility Funcs **************/

void PrintHeap(heap_t* heap)
{
    size_t i = 0;
    size_t size = HeapSize(heap);
    for (i = 0; i < size; ++i)
    {
        size_t lc_idx = i * 2 + 1;
        size_t rc_idx = lc_idx + 1;
        printf("p: %d\n", **((int**)(VECTOR(i))));
        
        if (rc_idx < size)
        {
            printf("l: %d\n", **((int**)(VECTOR(lc_idx))));
            printf("r: %d\n", **((int**)(VECTOR(rc_idx))));
            puts("");
            continue;
        }

        if (lc_idx < size)
        {
            printf("l: %d\n", **((int**)(VECTOR(lc_idx))));
        }
        puts("");
    }
}

/************* API Funcs ****************/

heap_t *HeapCreate(cmp_func_t cmp_func)
{
    heap_t* heap = (heap_t*)malloc(sizeof(heap_t));

    if (!heap)
    {
        heap = NULL;
        return NULL;
    }

    heap->vector = VectorCreate(SIZE, 4);

    if (!heap->vector)
    {
        free(heap);
        heap = NULL;
        return NULL;
    }

    heap->cmp_func = cmp_func;

    return heap;
}

void HeapDestroy(heap_t *heap)
{
    VectorDestroy(heap->vector);
    free(heap);
    heap = NULL;
}

size_t HeapSize(const heap_t *heap)
{
    return VectorSize(heap->vector);
}

int HeapIsEmpty(const heap_t *heap)
{
    return HeapSize(heap) == 0;
}

int HeapPush(heap_t *heap, void *data)
{
    if (VectorPushBack(heap->vector, &data))
    {
        return 1;
    }

    HeapifyUp(VECTOR(0),
                heap->cmp_func, HeapSize(heap) - 1, SIZE);

    return 0;
}

void HeapPop(heap_t *heap)
{
    size_t size = HeapSize(heap);
    
    Swap(VECTOR(0), 0, size - 1, SIZE);
    VectorPopBack(heap->vector);
    size = HeapSize(heap);
    HeapifyDown(VECTOR(0), heap->cmp_func, 0, SIZE, size);
}

void *HeapPeek(const heap_t *heap)
{
    if (HeapIsEmpty(heap))
    {
        return NULL;
    }

    return *(void**)VECTOR(0);
}

void *HeapRemove(heap_t *heap, const void *data, match_func_t match_func)
{
    void** arr = VECTOR(0);
    void* return_data = NULL;
    size_t i = 0;
    size_t size = HeapSize(heap);

    for (i = 0; i < size; ++i)
    {
        return_data = *(void**)VECTOR(i);

        if (match_func(data, return_data) == 0)
        {
            break;
        }
    }

    if (i == size)
    {
        return NULL;
    }

    Swap(arr, i, size - 1, SIZE);
    VectorPopBack(heap->vector);
    size = HeapSize(heap);
    HeapifyDown(arr, heap->cmp_func, i, SIZE, size);
    HeapifyUp(arr, heap->cmp_func, i, SIZE);

    return return_data;
}


