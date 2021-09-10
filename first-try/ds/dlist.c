#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include "dlist.h"


typedef struct dlist_node_t dlist_node_t;

struct dlist
{
    dlist_node_t* front;
    dlist_node_t* back;
};

struct dlist_node_t
{
    void* data;
    dlist_node_t* next;
    dlist_node_t* prev;
};

/**********************************************************************/

dlist_node_t* DListCreateNode(void* data, dlist_node_t* next, dlist_node_t* prev)
{
    dlist_node_t* new_node = malloc(sizeof(dlist_node_t));

    if (!new_node)
    {
        return NULL;
    }
    
    new_node->data = data;
    new_node->next = next;
    new_node->prev = prev;

    return new_node;   
}

int Count(void* data, void* param)
{
    (void)data;
    *(size_t*)param += 1;
    return 0;
}

/**********************************************************************/

dlist_t* DListCreate(void)
{
    dlist_node_t* front = NULL;
    dlist_node_t* back = NULL;
    dlist_t* new_dlist = NULL;

    front = DListCreateNode(NULL, NULL, NULL);

    if (!front)
    {
        return NULL;
    }

    back = DListCreateNode(NULL, NULL, NULL);

    if (!back)
    {
        free(front);
        front = NULL;
        return NULL;
    }

    new_dlist = malloc(sizeof(dlist_t));

    if (!new_dlist)
    {
        free(front);
        front = NULL;
        free(back);
        back = NULL;
        return NULL;
    }
    
    front->next = back;
    back->prev = front;
    new_dlist->front = front;
    new_dlist->back = back;

    return new_dlist;
}

void DListDestroy(dlist_t* dlist)
{
    dlist_node_t* current = NULL;
    dlist_node_t* to_remove = NULL;
    
    assert(dlist);

    current = dlist->front;
    
    while (current != NULL)
    {
        to_remove = current;
        current = current->next;
        free(to_remove);
        to_remove = NULL;
    }
    
    free(dlist);
    dlist = NULL;
}

int DListIsEmpty(const dlist_t* dlist)
{
    assert(dlist);

    return dlist->front->next == dlist->back;
}

dlist_iter_t DListInsert(dlist_t* dlist, dlist_iter_t iter, void* data)
{
	dlist_node_t* new_node = NULL;

	assert(dlist && iter);

	new_node = DListCreateNode(data, iter, iter->prev);

	if (!new_node)
	{
		return dlist->back;
	}
	
	new_node->prev->next = new_node;
	new_node->next->prev = new_node;

	return new_node;
}

dlist_iter_t DListPushFront(dlist_t* dlist, void* data)
{
	assert(dlist);

	return DListInsert(dlist, dlist->front->next, data);
}

dlist_iter_t DListPushBack(dlist_t* dlist, void* data)
{
	assert(dlist);

	return DListInsert(dlist, dlist->back, data);
}


void* DListGetData(dlist_iter_t iter)
{
	assert(iter);

	return iter->data;
}

dlist_iter_t DListBegin(const dlist_t* dlist)
{
	assert(dlist);

	return dlist->front->next;
}

dlist_iter_t DListEnd(const dlist_t* dlist)
{
	assert(dlist);

	return dlist->back;
}

dlist_iter_t DListRemove(dlist_iter_t iter)
{
	dlist_node_t* to_remove = NULL;

	assert(iter);
	
	if (iter->next == NULL) 
	
	{
		return iter;
	}
	
    if (iter->prev == NULL) 
	{
		return iter->next;
	}

	to_remove = iter;

	iter->prev->next = iter->next;
	iter->next->prev = iter->prev;
	iter = iter->next;

	free(to_remove);
	to_remove = NULL;

	return iter;
}

void* DListPopFront(dlist_t* dlist)
{
    void* data = NULL;

    assert(dlist);

    data = dlist->front->next->data;
    DListRemove(dlist->front->next);
    
    return data; 
}

void* DListPopBack(dlist_t* dlist)
{
    void* data = NULL;

    assert(dlist);

    data = dlist->back->prev->data;
    DListRemove(dlist->back->prev);
    
    return data; 
}

int DListIsSame(dlist_iter_t iter1, dlist_iter_t iter2)
{
    assert(iter1 && iter2);

    return iter1 == iter2;
}

dlist_iter_t DListNext(dlist_iter_t iter)
{
    assert(iter);
    
    return iter->next;
}

dlist_iter_t DListPrev(dlist_iter_t iter)
{
    assert(iter);
    
    return iter->prev;
}

dlist_iter_t DListSplice(dlist_iter_t dest, dlist_iter_t src_start, dlist_iter_t src_stop)
{
    dlist_iter_t tmp = {0};

    assert(dest && src_start && src_stop);

    if (DListIsSame(dest, src_start))
    {
        return dest;
    }

    tmp = src_start->prev;

    src_start->prev = dest->prev;
    src_start->prev->next = src_start;

    dest->prev = src_stop->prev;
    dest->prev->next = dest;

    tmp->next = src_stop;
    src_stop->prev = tmp;

    return dest;
}           

int DListForEach(dlist_iter_t iter_start, dlist_iter_t iter_end, int(*operation)(void*, void*), void* param)
{
    int return_value = 0;
 
    assert(iter_start && iter_end && operation);
       
    while (!return_value && iter_start != iter_end)
    {
        return_value = operation(iter_start->data, param);
        iter_start = iter_start->next;
    }

    return return_value;
}

dlist_iter_t DListFind(dlist_iter_t iter_start, dlist_iter_t iter_end, is_match_func match, const void* param)
{
    assert(iter_start && iter_end && match);
  
    while (iter_start != iter_end && match(iter_start->data, param))
    {    
        iter_start = iter_start->next;
    }

    return iter_start;
}

size_t DListSize(const dlist_t* dlist)
{
    size_t counter = 0;
    
    assert(dlist);
    
    DListForEach(DListBegin(dlist), DListEnd(dlist), &Count, &counter);

    return counter;
}









































































































