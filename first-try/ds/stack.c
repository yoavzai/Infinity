#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include "stack.h"

struct stack
{
    void* head;
    void* current;
    void* end;
    size_t size_of_element;

#ifndef NDEBUG
    size_t status;
#endif
};


#ifndef NDEBUG
int InvalidPointer(const stack_t* stack)
{
    if (stack == NULL || stack -> status != 0xDEADBEEF)
    {
        printf("Ivalid pointer!\n");
        return -1;
    }
    
    return 0;
}
#endif

/***********************************************************************************/

stack_t* StackCreate(size_t num_of_elements, size_t size_of_element)
{
    stack_t* new_stack = NULL;
   
#ifndef NDEBUG 
	if (num_of_elements == 0 || size_of_element == 0)
	{
		return NULL; 
	}
#endif  

	new_stack = malloc(sizeof(stack_t) + num_of_elements * size_of_element);	

	if (new_stack == NULL)
    {   
        return NULL;
    }

    new_stack -> head = (char*)new_stack + sizeof(stack_t);
    new_stack -> current = new_stack -> head;
    new_stack -> end = (char*)(new_stack -> head) + (num_of_elements * size_of_element);
    new_stack -> size_of_element = size_of_element;

#ifndef NDEBUG
    new_stack -> status = 0xDEADBEEF;
#endif

    return new_stack;
}

void StackDestroy(stack_t* stack)
{
#ifndef NDEBUG
    if (InvalidPointer(stack))
    {
        return;
    }
   
    stack -> status = 0;
#endif

    free(stack);
    stack = NULL;
}

int StackPush(stack_t* stack, const void* element)
{
#ifndef NDEBUG
    if (InvalidPointer(stack))
    {
        return -1;
    }
#endif

    if (stack -> current == stack -> end)
    {   
        assert(printf("stack is full\n"));
        return 0;  
    }

    memcpy(stack -> current, element, stack -> size_of_element);
    stack -> current = (char*)(stack -> current) + stack -> size_of_element;

    return 1;
}

void StackPop(stack_t* stack)
{
#ifndef NDEBUG
    if (InvalidPointer(stack))
    {
        return;
    }
#endif
    
    if (stack -> current == stack -> head)
    {
        assert(printf("Nothing to pop, stack is empty\n"));
        return;
    }
    
    stack -> current = (char*)stack -> current - stack -> size_of_element;
}

void* StackPeek(const stack_t* stack)
{
#ifndef NDEBUG
    if (InvalidPointer(stack))
    {
        return NULL;
    }
#endif    
    
    if (stack -> current == stack -> head)
    {
        return NULL;
    }

    return (char*)(stack -> current) - stack -> size_of_element;
}

size_t StackSize(const stack_t *stack)
{
#ifndef NDEBUG
    if (InvalidPointer(stack))
    {
        return 0;
    }
#endif

    return ((char*)(stack -> current) - (char*)(stack -> head)) / stack -> size_of_element;
}

int StackIsEmpty(const stack_t* stack)
{
#ifndef NDEBUG
	if (InvalidPointer(stack))
    {
        return -1;
    }
#endif

	return (stack -> current == stack -> head);
}
















