#include <stdio.h>
#include <stdlib.h>

#include "SList.h"
#include "test_functions.h"

#define RESET "\x1b[0m"

/*******************************************************************************/

#ifndef NDEBUG
void PrintList(slist_node_t* head)
{
    while (head != NULL)
    {
        printf(RESET"%d ", *(int*)(head->data));
        head = head->next;
    }
    puts("");  
}
#endif

int IsMatch(const void* data, void* param)
{
    return *(int*)data != *(int*)param;
}

int Operation(void* data, void* param)
{
    if (*(int*)data != 4)
    { 
        *(int*)data *= *(int*)param;
        return 0;
    }

    return 1;
}

/*******************************************************************************/

void TestOne()
{
    int i = 0;
    int arr[] = {1,2,3,4,5};
    slist_node_t* head = NULL;
    slist_node_t* iterator = NULL;

    for (i = 4; i >= 0; --i)
    {
        head = SListCreateNode(&arr[i], head); 
    }

    iterator = head;

    for (i = 0; i < 5; i++, iterator = iterator->next)
    {
        VerifyInt(*(int*)iterator->data, arr[i], "Create");
    }

    VerifyInt(*(int*)(SListRemoveAfter(head)->data), arr[2], "RemoveAfter");
    VerifyPointer(SListRemoveAfter(head->next->next->next), NULL, "RemoveAfter");
    VerifyPointer(SListRemoveAfter(head->next->next), NULL, "RemoveAfter");
    VerifyPointer(SListRemove(head->next->next), NULL, "Remove");
    VerifyInt(*(int*)(SListRemove(head)->data), arr[3], "Remove");
    VerifyPointer(SListRemove(head), NULL, "Remove");

    SListFreeAll(head);  
}

/*******************************************************************************/

void TestTwo()
{
    int flipped[] = {1,4,2,0,3};
    int num0 = 0;
    int num1 = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;
    int i = 0;

    slist_node_t* head = SListCreateNode(&num0, NULL);
    slist_node_t* node1 = SListCreateNode(&num1, NULL);
    slist_node_t* node2 = SListCreateNode(&num2, NULL);
    slist_node_t* node3 = SListCreateNode(&num3, NULL);
    slist_node_t* node4 = SListCreateNode(&num4, NULL);
    slist_node_t* iterator = NULL;
    
    VerifySizeT(SListCount(NULL), 0, "Count");
    VerifySizeT(SListCount(head), 1, "Count");
    VerifyInt(*(int*)(SListFlip(head)->data), 0, "Flip");
    
    SListInsertAfter(head, node1);
    
    VerifySizeT(SListCount(head), 2, "Count");

    VerifyInt(*(int*)head->data, 0, "InsertAfter");
    VerifyInt(*(int*)node1->data, 1, "InsertAfter");
    VerifyInt(*(int*)node1->data, *(int*)head->next->data , "InsertAfter");
    VerifyPointer(node1->next, NULL, "InsertAfter");

    SListInsertAfter(head, node2);

    VerifyInt(*(int*)node1->data, *(int*)node2->next->data , "InsertAfter");

    head = SListInsert(head, node3);

    VerifyInt(*(int*)head->data, 3, "Insert");
    VerifyInt(*(int*)node3->data, 0, "Insert");
    VerifyInt(*(int*)node3->data, *(int*)head->next->data , "Insert");
    VerifyInt(*(int*)node2->data, *(int*)node3->next->data , "Insert");
    node1 = SListInsert(node1, node4);
    VerifyPointer(node4->next, NULL, "Insert");
    VerifySizeT(SListCount(head), 5, "Count");

    head = SListFlip(head);
    iterator = head;
    
    for (i = 0; i < 5; i++, iterator = iterator->next)
    {
        VerifyInt(*(int*)iterator->data, flipped[i], "Flip");
    }

    SListFreeAll(head);
}

/*******************************************************************************/

void TestThree()
{
    int test_num = 3;
    int i = 0;
    int arr[] = {1,2,3,4,5};
    int arr_after_for_each[] = {3,6,9,4,5};
    slist_node_t* head = NULL;
    slist_node_t* iterator = NULL;
    is_match_func IsMatch_ptr = &IsMatch;
    operation_func Operation_ptr = &Operation;

    for (i = 4; i >= 0; --i)
    {
        head = SListCreateNode(&arr[i], head); 
    }

    VerifyInt(*(int*)(SListFind(head, &IsMatch_ptr, &arr[4])->data), arr[4], "Find");
    VerifyInt(*(int*)(SListFind(head, &IsMatch_ptr, &arr[2])->data), test_num, "Find");
    VerifyPointer(SListFind(head, &IsMatch_ptr, &i), NULL, "Find");
    iterator = SListCreateNode(&i, iterator);
    VerifyPointer(SListFind(iterator, &IsMatch_ptr, &arr[4]), NULL, "Find (Looped List)");
    iterator->next = NULL;
    SListFreeAll(iterator);

    SListForEach(head, &Operation_ptr, &test_num);
    iterator = head;

    for (i = 0; i < 5; ++i, iterator = iterator->next)
    { 
        VerifyInt(*(int*)iterator->data, arr_after_for_each[i], "ForEach");    
    }
    
    SListFreeAll(head);
}

/*******************************************************************************/

void TestFour()
{
    int num0 = 0;
    int num1 = 1;
    int num2 = 2;
    int num3 = 3;
    int num4 = 4;
    int num5 = 5;
    slist_node_t* head = SListCreateNode(&num0, NULL);
    slist_node_t* node1 = SListCreateNode(&num1, NULL);
    slist_node_t* node2 = SListCreateNode(&num2, NULL);
    slist_node_t* head2 = SListCreateNode(&num3,
                          SListCreateNode(&num4,
                          SListCreateNode(&num5, NULL)));
    
    VerifyInt(SListHasLoop(head), 0, "HasLoop");
    head->next = head;
    VerifyInt(SListHasLoop(head), 1, "HasLoop");
    head->next = node1;
    node1->next = node2;
    VerifyInt(SListHasLoop(head), 0, "HasLoop");
    node2->next = head;
    VerifyInt(SListHasLoop(head), 1, "HasLoop");
    node2->next = node1;
    VerifyInt(SListHasLoop(head), 1, "HasLoop");
    node2->next = node2;
    VerifyInt(SListHasLoop(head), 1, "HasLoop");
    VerifySizeT(SListCount(head), 0, "Count (Looped List)");
    VerifyPointer(SListFindIntersection(head, head2),
                  NULL, "FindIntersection (Looped List)");
    VerifyPointer(SListFlip(head), NULL, "Flip (Looped List)");

    node2->next = NULL;

    VerifyInt(*(int*)SListFindIntersection(head, head->next)->data,
              num1, "FindIntersection");
    
    VerifyPointer(SListFindIntersection(head, head2),
                  NULL, "FindIntersection");

    head2->next->next->next = head;
    VerifyInt(*(int*)SListFindIntersection(head, head2)->data,
              num0, "FindIntersection");

    head2->next->next->next = head->next->next;
    VerifyInt(*(int*)SListFindIntersection(head2, head)->data,
              num2, "FindIntersection");

    head2->next->next->next = NULL;

    SListFreeAll(head);
    SListFreeAll(head2);
}

/*******************************************************************************/    

int main()
{
    
    TestOne();  /* Create, RemoveAfter, Remove, FreeAll */
    TestTwo();  /* Insert, InsertAfter, Count, Flip */
    TestThree(); /* Find, ForEach */
    TestFour(); /* HasLoop FindIntersection */

    return 0;
}

