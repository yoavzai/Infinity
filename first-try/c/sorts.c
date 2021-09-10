#include <stddef.h> /* size_t, ptrdiff */
#include <stdlib.h> /* calloc,free */
#include <string.h> /* memcpy */

#include "sorts.h"
#include "heapify.h"

typedef int (*key_func_t)(int num, int base, int shift);
typedef enum {DECREASING = -1, INCREASING = 1} oreder_t;


static size_t MinIdx(int* arr, size_t i, size_t size);
static int GetShift(int base);
static int KeyForPwrsOf2(int num, int base, int shift);
static int KeyForAnyBase(int num, int base, int shift);
static int Pow(int base, int exp);
static int Max(int* arr, size_t size);
static int GetNdigits(int num, int base);
static void SwapPtrs(int** src, int** dest);
static void Merge(int* dest, int* left, int* right, size_t lsize, size_t rsize);
static void GenericSwap(void* arr, size_t idx1, size_t idx2,
                        size_t size_e, void* buffer);
static size_t Partition(void* arr, size_t size_e, size_t num_e,
                    cmp_func_t cmp_func, void* buffer);                        
static int cmp_func(const void* data1,const void* data2);
static void InnerQuickSort(void* arr, size_t size_e, size_t num_e,
                            cmp_func_t cmp_func, void* buffer);

/**************** Utility Funcs *****************/

static int cmp_func(const void* data1,const void* data2)
{
    return *(int*)data1 - *(int*)data2;
}

static size_t MinIdx(int* arr, size_t i, size_t size)
{
    size_t min_idx = i;

    for (i = i + 1; i < size; i++)
    {
        if (arr[i] < arr[min_idx])
        {
            min_idx = i;
        }
    }

    return min_idx;
}

static int GetShift(int base)
{
    int shift = 0;

    if (!(base & (base - 1)))
    {
        while (base > 1)
        {
            base >>= 1;
            shift++;
        }
    }

    return shift;
}

static int KeyForPwrsOf2(int num, int base, int shift)
{
    int mask = base - 1;

    return mask & (num >> shift);
}

static int KeyForAnyBase(int num, int base, int shift)
{
    num /= shift;

    return num % base;
}

static int Pow(int base, int exp)
{
    int result = 1;

    while (exp > 0)
    {
        result *= base;
        --exp;
    }

    return result;
}

static int Max(int* arr, size_t size)
{
    size_t i = 1;
    int max = arr[0];

    for (i = 1; i < size; ++i)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    return max;
}

static int GetNdigits(int num, int base)
{
    int ndigits = 0;

    while (num != 0)
    {
        num /= base;
        ++ndigits;
    }

    return ndigits;
}

static void SwapPtrs(int** src, int** dest)
{
    int* tmp = *src;
    *src = *dest;
    *dest = tmp;
}

/*********************************************************/

void BubbleSort(int* arr, size_t size)
{
    size_t niter = size - 1;
    size_t i = 0;
    size_t last_swaped = 0;

    while (niter > 0)
    {
        for (i = 0; i < niter; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                Swap(arr, i, i + 1);
                last_swaped = i;
            }
        }

        niter = last_swaped;
        last_swaped = 0;
    }
}

void InsertionSort(int* arr, size_t size)
{
    size_t i = 0;
    size_t j = 0;

    for (i = 1; i < size; i++)
    {
        j = i;
        
        while (j > 0 && arr[j] < arr[j - 1])
        {
            Swap(arr, j - 1, j);
            j--;
        }
    }
}

void SelectionSort(int* arr, size_t size)
{
    size_t i = 0;
    size_t min_idx = 0;

    for (i = 0; i < size; i++)
    {
        min_idx = MinIdx(arr, i, size);
        Swap(arr, min_idx, i);
    }
}

void CountingSort(int* arr, int* dest, size_t size, int min, int max)
{
    ptrdiff_t i = 0;
    int aux_size = max - min + 1;
    size_t* aux = (size_t*)calloc(aux_size, sizeof(size_t));

    if (!aux)
    {
        return;
    }

    for (i = 0; i < (ptrdiff_t)size; ++i)
    {
        aux[arr[i] - min]++;
    }

    for (i = 1; i < aux_size; ++i)
    {
        aux[i] += aux[i - 1];
    }

    for (i = size - 1; i >= 0; --i)
    {
        dest[--aux[arr[i] - min]] = arr[i];
    }

    free(aux);
}

void CountingSortForRadix(int* src, int* dest, size_t size, key_func_t key_func,
                            int base, int shift, int digit)
{
    ptrdiff_t i = 0;
    size_t* aux = (size_t*)calloc(base, sizeof(size_t));

    if (!aux)
    {
        return;
    }

    if (shift == 0) /* if base is not power of 2 */
    {
        shift = Pow(base, digit - 1);
    }
    else /* base is power of 2 */
    {
        shift *= digit - 1;
    }

    for (i = 0; i < (ptrdiff_t)size; ++i)
    {
        aux[key_func(src[i], base, shift)]++;
    }

    for (i = 1; i < base; ++i)
    {
        aux[i] += aux[i - 1];
    }

    for (i = size - 1; i >= 0; --i)
    {
        dest[--aux[key_func(src[i], base, shift)]] = src[i];
    }

    free(aux);
}

void RadixSort(int* arr, size_t size, int base)
{
    int* src = NULL;
    int* dest = NULL;
    int cur_digit = 1;
    int ndigits = GetNdigits(Max(arr, size), base);
    int shift = GetShift(base); /* if base is pwr of 2 return the shift else return 0 */
    key_func_t key_func = KeyForAnyBase;

    if (shift != 0)
    {
        key_func = KeyForPwrsOf2;
    }

    if (!(src = (int*)malloc(size * sizeof(int))))
    {
        return;
    }

    if (!(dest = (int*)malloc(size * sizeof(int))))
    {
        free(src);
        src = NULL;
        return;
    }

    memcpy(src, arr, size * sizeof(int));

    for (cur_digit = 1; cur_digit <= ndigits; ++cur_digit)
    {
        CountingSortForRadix(src, dest, size, key_func, base, shift, cur_digit);
        SwapPtrs(&src, &dest);
    }

    memcpy(arr, src, size * sizeof(int));

    free(src);
    free(dest);
    src = NULL;
    dest = NULL;
}

void MergeSort(int* dest, int* src, size_t size)
{
    size_t lsize = size / 2;
    size_t rsize = size - lsize;
    int* left = src;
    int* right = src + lsize;

    if (size == 1)
    {
        return;
    }

    MergeSort(dest, left, lsize);
    MergeSort(dest, right, rsize);
    Merge(dest, left, right, lsize, rsize);
    memcpy(src, dest, size * sizeof(int));
}

void Merge(int* dest, int* left, int* right, size_t lsize, size_t rsize)
{
    size_t lidx = 0;
    size_t ridx = 0;

    while (lidx < lsize && ridx < rsize)
    {
        if (left[lidx] <= right[ridx])
        {
            dest[lidx + ridx] = left[lidx];
            lidx++;
        }

        else
        {
            dest[lidx + ridx] = right[ridx];
            ridx++;
        }
    }

    while (lidx < lsize)
    {
        dest[lidx + ridx] = left[lidx];
        lidx++;
    }

    while (ridx < rsize)
    {
        dest[lidx + ridx] = right[ridx];
        ridx++;
    }
}

static void GenericSwap(void* arr, size_t idx1, size_t idx2,
                        size_t size_e, void* buffer)
{
    memcpy(buffer, (char*)arr + idx1 * size_e, size_e);
    memcpy((char*)arr + idx1 * size_e, (char*)arr + idx2 * size_e, size_e);
    memcpy((char*)arr + idx2 * size_e, buffer, size_e);
}

static size_t Partition(void* arr, size_t size_e, size_t num_e,
                    cmp_func_t cmp_func, void* buffer) 
{ 
    size_t first_bigger_idx = num_e - 1;
    size_t final_pivot_idx = num_e;

    for (; first_bigger_idx > 0; first_bigger_idx--)
    {
        if (cmp_func(arr, (char*)arr + first_bigger_idx * size_e) < 0)
        {
            final_pivot_idx--;
            GenericSwap(arr, first_bigger_idx, final_pivot_idx, size_e, buffer);
        }
    }

    final_pivot_idx--;
    GenericSwap(arr, 0, final_pivot_idx, size_e, buffer);

    return final_pivot_idx;
} 
  
static void InnerQuickSort(void* arr, size_t size_e, size_t num_e,
                            cmp_func_t cmp_func, void* buffer)
{
    size_t pivot_idx = 0;

    if (num_e < 2)
    {
        return;
    }

    pivot_idx = Partition(arr, size_e, num_e, cmp_func, buffer);

    InnerQuickSort(arr, size_e, pivot_idx, cmp_func, buffer);
    InnerQuickSort((char*)arr + ((pivot_idx + 1) * size_e), size_e,
                    num_e - (pivot_idx + 1), cmp_func, buffer);
} 

void QuickSort(void* arr, size_t size_e, size_t num_e, cmp_func_t cmp_func) 
{
    void* buffer = malloc(size_e);

    if (buffer == NULL)
    {
        return;
    }

    InnerQuickSort(arr, size_e, num_e, cmp_func, buffer);
}


void HeapSort(int* arr, size_t size)
{
    size_t idx = size;

    while (idx > 0)
    {
        HeapifyDown(arr, cmp_func, idx - 1, sizeof(int), size);
        --idx;
    }

    while (size > 1)
    {
        Swap(arr, 0, size - 1);
        --size;
        HeapifyDown(arr, cmp_func, 0, sizeof(int), size);
    }
}