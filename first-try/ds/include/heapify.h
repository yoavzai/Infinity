#ifndef _HEAPIFY_
#define _HEAPIFY_

#include "heap.h"

void HeapifyUp(void* arr, cmp_func_t cmp_func, size_t idx, size_t selement);
void HeapifyDown(void* arr, cmp_func_t cmp_func, size_t idx,
                        size_t selement, size_t nelements);
void Swap(void* arr, size_t idx1, size_t idx2, size_t selement);

#endif