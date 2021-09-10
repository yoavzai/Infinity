#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "sorted_list.h"
#include "dlist.h"

struct sorted_list
{
    is_before_t is_before;
    const void* param;
    dlist_t* dlist;
};

srlist_t* SortedListCreate(is_before_t is_before, const void* param)
{
    srlist_t* new_srlist;    

    assert(is_before);

    new_srlist = malloc(sizeof(srlist_t));

    if (!new_srlist)
    {
        return NULL;
    }
    new_srlist->dlist = DListCreate();

    if (!new_srlist->dlist)
    {
        free(new_srlist);
        new_srlist = NULL;
        return NULL;
    }

    new_srlist->is_before = is_before;
    new_srlist->param = param;
 
    return new_srlist;
}

void SortedListDestroy(srlist_t* srlist)
{
    assert(srlist);

    DListDestroy(srlist->dlist);
    free(srlist);
    srlist = NULL;
}

size_t SortedListSize(const srlist_t* srlist)
{
    assert(srlist);
    
    return DListSize(srlist->dlist);
}

int SortedListIsEmpty(const srlist_t* srlist)
{
    assert(srlist);

    return DListIsEmpty(srlist->dlist);
}

void* SortedListGetData(sorted_list_iter_t iter)
{
    return DListGetData(iter.internal_itr);
}

sorted_list_iter_t SortedListBegin(srlist_t* srlist)
{
    sorted_list_iter_t new_iter = {0};
    
    assert(srlist);
    
    new_iter.internal_itr = DListBegin(srlist->dlist);

    return new_iter;
}

sorted_list_iter_t SortedListEnd(srlist_t* srlist)
{
    sorted_list_iter_t new_iter = {0};
    
    assert(srlist);
    
    new_iter.internal_itr = DListEnd(srlist->dlist);

    return new_iter;
}

sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter)
{
    iter.internal_itr = DListPrev(iter.internal_itr);

    return iter;
}

sorted_list_iter_t SortedListNext(sorted_list_iter_t iter)
{
    iter.internal_itr = DListNext(iter.internal_itr);

    return iter;
}

int SortedListIsSameIter(sorted_list_iter_t iter1, sorted_list_iter_t iter2)
{
    return iter1.internal_itr == iter2.internal_itr;
}

sorted_list_iter_t SortedListInsert(srlist_t* srlist, void* data)
{
	sorted_list_iter_t iter = {0};
	
	assert(srlist);

    iter = SortedListBegin(srlist);

    while (!SortedListIsSameIter(iter, SortedListEnd(srlist)) &&
            srlist->is_before(SortedListGetData(iter), data, srlist->param))
    {
        iter = SortedListNext(iter);
    }

	iter.internal_itr = DListInsert(srlist->dlist, iter.internal_itr, data);

	return iter;
}

sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter)
{
    iter.internal_itr = DListRemove(iter.internal_itr);

    return iter;
}


void* SortedListPopFront(srlist_t* srlist)
{
    assert(srlist);

    return DListPopFront(srlist->dlist);
}

void* SortedListPopBack(srlist_t* srlist)
{
    assert(srlist);
    
    return DListPopBack(srlist->dlist);
}

int SortedListForEach(sorted_list_iter_t start, sorted_list_iter_t stop, 
                        int(*operation)(void* data, void* param), void* param)
{
    return DListForEach(start.internal_itr, stop.internal_itr, operation, param);
}

sorted_list_iter_t SortedListFind(srlist_t* srlist, sorted_list_iter_t start,
                            sorted_list_iter_t stop, const void* to_find)
{   
    assert(srlist);

    while (!SortedListIsSameIter(start, stop) &&
           srlist->is_before(SortedListGetData(start), to_find, srlist->param))
    {
        start = SortedListNext(start);
    }

    if (!SortedListIsSameIter(start, stop) && 
        !srlist->is_before(to_find, SortedListGetData(start), srlist->param))
    {
        return start;
    }

    return stop;
}

sorted_list_iter_t SortedListFindIf(sorted_list_iter_t start,
                                    sorted_list_iter_t stop,
                                    int(*match)(const void* data,
                                    const void* param), const void* param)
{
    while (!SortedListIsSameIter(start, stop) &&
           match(SortedListGetData(start), param))
    {
        start = SortedListNext(start);
    }

    return start;
}

sorted_list_iter_t SortedListFindIf2(sorted_list_iter_t start,
                                    sorted_list_iter_t stop,
                                    int(*match)(const void* data1,
                                    const void* data2, const void* param),
                                    const void* data, const void* param)
{
    while (!SortedListIsSameIter(start, stop) &&
           match(SortedListGetData(start), data, param))
    {
        start = SortedListNext(start);
    }

    return start;
}

void SortedListMerge(srlist_t* dest, srlist_t* src)
{
    sorted_list_iter_t cur_dest;
    sorted_list_iter_t start_splice;
    sorted_list_iter_t end_splice;

    assert(dest && src);

    cur_dest = SortedListBegin(dest);
    start_splice = SortedListBegin(src);

    while (!SortedListIsEmpty(src))
    {
        cur_dest = SortedListFindIf2(cur_dest, SortedListEnd(dest),
                    dest->is_before, SortedListGetData(start_splice),
                    dest->param);
        
        if (SortedListIsSameIter(cur_dest, SortedListEnd(dest)))
        {
            end_splice = SortedListEnd(src);
        }

        else
        {
            end_splice = SortedListFindIf2(SortedListNext(start_splice),
                            SortedListEnd(src), src->is_before,
                            SortedListGetData(cur_dest), src->param);
        }
        
        DListSplice(cur_dest.internal_itr, start_splice.internal_itr,
                    end_splice.internal_itr);

        start_splice = end_splice;    
    }
}

















