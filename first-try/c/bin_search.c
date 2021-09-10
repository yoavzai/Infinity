#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */

typedef int (*cmp_func_t)(const void* data1, const void* data2);

void* BinSearchRec(const void* base, size_t num_el,
                    size_t el_size, const void* requested_data,
                     cmp_func_t cmp_func)
{
    size_t mid_idx = num_el / 2;
    void* cur_data = (char*)base + mid_idx * el_size;
    int status = 0;

    if (num_el == 0)
    {
        return NULL;
    }
    
    status = cmp_func(cur_data, requested_data);

    if (status == 0) /* found */
    {
        return cur_data;
    }

    else if (status < 0) /* right side */
    {
        base = (char*)base + (mid_idx + 1) * el_size;
        num_el = num_el - mid_idx + 1;
    }

    else /* left side */
    {
        num_el = mid_idx;
    }

    return BinSearchRec(base, num_el, el_size, requested_data, cmp_func);
}                     

int cmp_func(const void* data1, const void* data2)
{
    return *(int*)data1 - *(int*)data2;
}

int main()
{
    int num = 10;
    int num2 = 7;
    int arr[] = {1,2,3,4,5,6,7,8,9};
    void* data = BinSearchRec(arr, sizeof(arr)/sizeof(arr[0]), sizeof(arr[0]), &num2, cmp_func);
    void* data2 = BinSearchRec(arr, sizeof(arr)/sizeof(arr[0]), sizeof(arr[0]), &num, cmp_func);

    printf("%d\n%p\n", *(int*)data, data2);

    return 0;
}