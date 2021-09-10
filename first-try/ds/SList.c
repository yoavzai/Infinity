#include <stdlib.h> /* malloc, free */
#include <errno.h> /* errno */
#include <stdio.h> /* fprintf */
#include <assert.h> /* assert */
#include <string.h> /* strerror */

#include "SList.h"


slist_node_t* SListCreateNode(void* data, slist_node_t* next)
{
    slist_node_t* new_node = malloc(sizeof(slist_node_t));
    
    if (!new_node)
    {
        assert(fprintf(stderr, "Error: %s", strerror(errno)));
        return NULL;
    }
    
    new_node->data = data;
    new_node->next = next;

    return new_node;
}

slist_node_t* SListInsertAfter(slist_node_t *target, slist_node_t *new_node)
{
    if (target == NULL || new_node == NULL)
    {
        return NULL;        
    }

    new_node->next = target->next;
    target->next = new_node;

    return new_node;
}

slist_node_t* SListInsert(slist_node_t *target, slist_node_t *new_node)
{
    void* temp = target->data;
    
    target->data = new_node->data;
    new_node->data = temp;
    new_node->next = target->next;
    target->next = new_node;

    return target;
}

size_t SListCount(const slist_node_t *head)
{
    size_t counter = 0;

    if (head == NULL)
    {
        return 0;    
    }

    if (SListHasLoop(head))
    {
        return 0;    
    }

    while (head != NULL)
    {
        ++counter;
        head = head->next;
    }

    return counter;
}

void SListFreeAll(slist_node_t *head)
{
    slist_node_t* temp = NULL;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
        temp = NULL;
    }
}

slist_node_t* SListRemoveAfter(slist_node_t *target)
{
    slist_node_t* to_remove = NULL;

    if (target == NULL || target->next == NULL)
    {
        return NULL;        
    }

    to_remove = target->next;
    target->next = to_remove->next;
    free(to_remove);
    to_remove = NULL;
   
    return target->next;
}

slist_node_t* SListRemove(slist_node_t *target)
{
    if (target->next == NULL)
    {
        return NULL;
    }

    target->data = target->next->data;
  
    return SListRemoveAfter(target);
}

slist_node_t* SListFlip(slist_node_t* head)
{
    slist_node_t* temp1 = NULL;
    slist_node_t* temp2 = NULL;

    if (SListHasLoop(head))
    {
        return NULL;    
    }

    while (head->next != NULL)
    {
        temp2 = head->next;
        head->next = temp1;
        temp1 = head;
        head = temp2;
    }

    head->next = temp1;

    return head;
}

slist_node_t *SListFind(slist_node_t *head, is_match_func *match, void *param)
{
    if (SListHasLoop(head))
    {
        return NULL;    
    }

    while (head != NULL)
    {
        if (!(*match)(head->data, param))
        {
            break;
        }

        head = head->next;
    }

    return head;
}

void SListForEach(slist_node_t* head, operation_func* operation, void* param)
{
    if (SListHasLoop(head))
    {
        return;    
    }

    while (head != NULL)
    {
        if ((*operation)(head->data, param))
        {
            break;
        }

        head = head->next;
    }
}

int SListHasLoop(const slist_node_t* head)
{
    slist_node_t* fast_ptr = NULL;

    if (head == NULL)
    {
        return 0;
    }

    if (head->next == NULL)
    {
        return 0;
    }
    
    fast_ptr = head->next;

    while (fast_ptr->next != NULL)
    {
        if (fast_ptr == head)
        {
            return 1;
        }

        fast_ptr = fast_ptr->next->next;

        if (fast_ptr == NULL)
        {
            return 0;
        }

        head = head->next;
    }

    return 0;    
}

slist_node_t* SListFindIntersection(slist_node_t* head1, slist_node_t* head2)
{
    slist_node_t* big = head1;
    slist_node_t* small = head2;
    ptrdiff_t diff = 0;

    if (SListHasLoop(head1) || SListHasLoop(head2))
    {
        return NULL;    
    }

    diff = SListCount(head1) - SListCount(head2);

    if (diff < 0)
    {
        big = head2;
        small = head1;
        diff *= -1;
    }

    while (diff > 0)
    {
        big = big->next;
        --diff;
    }

    while (big != small)
    {
        big = big->next;
        small = small->next;
    }

    return big;
}

