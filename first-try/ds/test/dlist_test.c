#include <stdio.h>

#include "dlist.h"
#include "test_functions.h"

int main()
{
    size_t i = 0;
    int nums[] = {0,1,2,3,4};
    int nums2[] = {5,6,7,8,9};
    dlist_iter_t iter = NULL;
    dlist_t* dlist = DListCreate();
    dlist_t* dlist2 = DListCreate();
	

    /* dlist = 4,3,2,1,0; dlist2 = 9,8,7,6,5 */
    for (i = 0; i < 5; ++i)
    {
        DListPushFront(dlist, &nums[i]);
        DListPushFront(dlist2, &nums2[i]);
    }

    VerifySizeT(DListSize(dlist), 5, "Size");

    iter = DListBegin(dlist);

    /* iterates over dlist from begin till end*/
    for (i = 0; !DListIsSame(iter, DListEnd(dlist)); ++i, iter = DListNext(iter))
    {
        VerifyPointer(DListGetData(iter), &nums[4 - i], "IsSame End Next GetData"); 
    }
    
    /* empty dlist */
    for (i = 0; i < 5; ++i)
        {
            VerifyPointer(DListPopBack(dlist), &nums[i], "Pop");
        }
    
    VerifyInt(DListIsEmpty(dlist), 1, "IsEmpty");

    /* dlist = 9,8,7,6,5; dlist2 = */
    iter = DListSplice(DListEnd(dlist), DListBegin(dlist2), DListEnd(dlist2));
    VerifyInt(DListIsEmpty(dlist2), 1, "IsEmpty");
    VerifyInt(DListIsSame(iter, DListEnd(dlist)), 1, "Splice");

    iter = DListPrev(DListEnd(dlist));

for (i = 0; !DListIsSame(iter, DListPrev(DListBegin(dlist))); ++i, iter = DListPrev(iter))
    {
        VerifyPointer(DListGetData(iter), &nums2[i], "Prev Begin Splice"); 
    }
    
	DListDestroy(dlist);
    DListDestroy(dlist2);

    return 0;
}
