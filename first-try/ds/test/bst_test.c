#include <stdio.h>

#include "bst.h"

int cmp(const void *data1, const void *data2, void *param)
{
    param = param;
    return *((int *)data1) - *((int *)data2);
}

int main()
{
    bst_t *my_bst = BSTCreate(cmp, NULL);

    printf("bst %p\nbst->begin %p\nbst->end %p\n", (void *)my_bst, (void *)BSTBegin(my_bst), (void *)BSTEnd(my_bst));

    BSTDestroy(my_bst);

    return 0;
}