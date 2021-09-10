#include <string.h> /* memcpy */
#include <unistd.h> /* ssize_t */
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc, free */

#include "heapify.h"

static int IsParentSmaller(void* arr, cmp_func_t cmp_func,
                         size_t p_idx, size_t c_idx, size_t selement)
{
    return cmp_func((char*)arr + c_idx * selement,
                    (char*)arr + p_idx * selement) > 0;
}

void Swap(int* arr, size_t i, size_t j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

/* returns idx to bigger chlild. if only one child returns its idx.
 if no children returns -1 */
static ssize_t GetMaxChildIdx(void* arr, cmp_func_t cmp_func, size_t p_idx,
                         size_t selement, size_t nelements )
{
    size_t c1_idx = p_idx * 2 + 1;
    size_t c2_idx = c1_idx + 1;

    if (c1_idx >= nelements)
    {
        return -1;
    }
    
    if (c2_idx >= nelements)
    {
        return c1_idx;
    }

    return cmp_func((char*)arr + c1_idx * selement,
                    (char*)arr + c2_idx * selement) > 0 ? c1_idx : c2_idx;
}

void HeapifyUp(void* arr, cmp_func_t cmp_func, size_t idx, size_t selement)
{
    size_t p_idx = (idx - 1) / 2;

    while (idx > 0 && IsParentSmaller(arr, cmp_func, p_idx, idx, selement))
    {
        Swap(arr, idx, p_idx);
        idx = p_idx;
        p_idx = (idx - 1) / 2;
    }
}

void HeapifyDown(void* arr, cmp_func_t cmp_func, size_t idx,
                        size_t selement, size_t nelements)
{
    ssize_t c_idx = GetMaxChildIdx(arr, cmp_func, idx, selement, nelements);

    while (c_idx > -1 && IsParentSmaller(arr, cmp_func, idx, c_idx, selement))
    {
        Swap(arr, idx, c_idx);
        idx = c_idx;
        c_idx = GetMaxChildIdx(arr, cmp_func, c_idx, selement, nelements);
    }
}                        
