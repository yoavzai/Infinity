#include <stdio.h> /* printf */

#include "stack.h"

void PrintStack(stack_t* stack)
{
    int i = 0;
    int* ptr = (int*)StackPeek(stack);

    for (i = 0; i < 4; i++, ptr--)
    {
        printf("%d ", *ptr);
    }

    puts("");
}

void EmptyStack(stack_t* stack)
{
    while (!StackIsEmpty(stack))
    {
        StackPop(stack);
    }
}
    
/***************************************************************/

void PutNumInPlace(stack_t* stack, int num)
{
    int cur_num = 0;

    if (StackIsEmpty(stack) || num >= *(int*)StackPeek(stack))
    {
        StackPush(stack, &num);
        return;
    }

    cur_num = *(int*)StackPeek(stack);
    StackPop(stack);
    PutNumInPlace(stack, num);
    StackPush(stack, &cur_num);
}

void Sort(stack_t* stack)
{
    int num = 0;

    if (StackSize(stack) < 2)
    {
        return;
    }

    num = *(int*)StackPeek(stack);
    StackPop(stack);
    Sort(stack);
    PutNumInPlace(stack, num);
}

int main()
{
    int i = 0;
    int j = 0;
    int arr[4][4] = {{0,-1,2,-3}, {0,0,1,0}, {3,2,1,0}, {2,3,7,4}};
    stack_t* stack = StackCreate(4, sizeof(int));
    
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            StackPush(stack, &arr[i][j]);
        }

        PrintStack(stack);
        Sort(stack);
        PrintStack(stack);
        EmptyStack(stack);
        puts("");

    }

    StackDestroy(stack);

    return 0;
}











