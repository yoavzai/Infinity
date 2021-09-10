#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl.h"
#include "avl_main.h"

#define ARR_SIZE 10
#define RED "\033[22;31m"
#define GREEN "\033[22;32m"
#define RESET "\x1B[0m"
#define REQUIRE(x,y) (x == y ? printf(GREEN"SUCCESS\n"RESET) : printf(RED"FAIL\n"RESET))

/*

ForEach with no nodes

*/
int InOrderPrintSome(void* data, void* param)
{
    int cur_num = *(int*)data;
    (void)param;

    if (cur_num < 20)
    {
        return 0;
    }

    if (cur_num < 30)
    {
        if (cur_num % 2 == 0)
        {
            printf("%d, ", *(int*)data);        
        }
        
        return 0;
    }

    return 1;
}

int FindIfFunc(const void* data, void* param)
{
    int cur_num = *(int*)data;

    if (cur_num % 7 == 0 && cur_num > 14 && cur_num != *(int*)param)
    {
        return 1;
    }

    return 0;
}

int InOrderPrint(void* data, void* param)
{
    (void)param;
    printf("%d, ", *(int*)data);
    return 0;
}

int cmp_func(const void *data1, const void *data2, void *param)
{
    (void)param;

    return *(int*)data1 - *(int*)data2;
}

void PrintNode(avl_node_t root)
{
    if (root == NULL)
    {
        return;
    }

    else
    {
        printf("ROOT: %d\nHEIGHT: %lu\n", *(int*)root->data, root->height);
    }
    

    if (root->child[LEFT] == NULL)
    {
        printf("LEFT: NULL\n");
    }

    else
    {
        printf("LEFT: %d\n", *(int*)root->child[LEFT]->data);
    }
    
    if (root->child[RIGHT] == NULL)
    {
        printf("RIGHT: NULL\n");
    }

    else
    {
        printf("RIGHT: %d\n", *(int*)root->child[RIGHT]->data);
    }
    puts("");

    PrintNode(root->child[LEFT]);
    PrintNode(root->child[RIGHT]);
}

void PrintAVL(avl_t* avl)
{
    PrintNode(avl->root);
}

void Shuffle(int* arr, size_t size)
{
    size_t i = 0;
    int tmp = 0;
    int rand_idx = 0;
    srand(time(NULL));

    for (i = 0; i < size; ++i)
    {
        rand_idx = rand()%size;
        
        if (arr[i] == (int)i && arr[rand_idx] == rand_idx)
        {
            tmp = arr[rand_idx];
            arr[rand_idx] = arr[i];
            arr[i] = tmp;
        }
    }
}

int main()
{
    /*
    int num = 21;
    int not_in_tree = 0;
    */

    int arr[ARR_SIZE];
    size_t i = 0;

    /*
    size_t size = sizeof(arr)/sizeof(arr[0]);
    */

    avl_t* avl = AVLCreate(cmp_func, NULL);
    
    /*
    printf("IsEmpty ");
    REQUIRE(AVLIsEmpty(avl), 1);
    printf("Size ");
    REQUIRE(AVLSize(avl), 0);
    */

    for (i = 0; i < ARR_SIZE; ++i)
    {
        arr[i] = i;   
    }

    Shuffle(arr, ARR_SIZE);

    for (i = 0; i < ARR_SIZE; ++i)
    {
        AVLInsert(avl, &arr[i]);
        printf("%d, ", arr[i]);
    }

    PrintAVL(avl);
    puts("------------------");

    for (i = 0; i < ARR_SIZE; ++i)
    {
        AVLRemove(avl, &arr[i]);
        PrintAVL(avl);
        AVLRemove(avl, &arr[i]);
        PrintAVL(avl);
        puts("------------------");
    }

    AVLRemove(avl, &arr[i]);
    PrintAVL(avl);

    /*
    printf("Height ");
    REQUIRE(AVLHeight(avl), 3);
    printf("Size ");
    REQUIRE(AVLSize(avl), size);
    printf("Find ");
    REQUIRE(AVLFind(avl, &arr[0]), &arr[0]);
    printf("Find ");
    REQUIRE(AVLFind(avl, &not_in_tree), NULL);
    AVLForEach(avl, InOrderPrint, NULL);
    puts("");
    */

    /*
    printf("%d\n", *(int*)AVLFindIf(avl, FindIfFunc, &num));
    printf("%lu\n", AVLHeight(avl));
    */

    AVLDestroy(avl);

    return 0;
}