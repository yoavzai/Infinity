#ifndef SORTS
#define SORTS

#include <stddef.h> /* size_t */

typedef int (*cmp_func_t)(const void* data1,const void* data2);

void BubbleSort(int* arr, size_t size);
void InsertionSort(int* arr, size_t size);
void SelectionSort(int* arr, size_t size);
void CountingSort(int* arr, int* dest, size_t size, int min, int max);
void RadixSort(int* arr, size_t size, int base);
void MergeSort(int* dest, int* src, size_t size);
void HeapSort(int* arr, size_t size);
void QuickSort(void* arr, size_t size_e, size_t num_e, cmp_func_t cmp_func);

#endif