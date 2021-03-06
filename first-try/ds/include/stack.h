#ifndef _STACK_H_
#define _STACK_H_

/* Rev. 1.1 */ 
/* 28.8.19  12:30 */

#include <stddef.h>

typedef struct stack stack_t;

/* returns pointer to a new stack on success. returns NULL on failure. complexity of malloc function */
stack_t* StackCreate(size_t num_of_elements, size_t size_of_element);

/* after execution the pointer to the stack will be invalid. complexity of free function */
void StackDestroy(stack_t* stack);

/* adds an element to top of the stack. returns 1 on success, 0 when stack is full
   and -1 when invalid pointer was given. complexity of O(n) */
int StackPush(stack_t* stack, const void* element);

/* removes top element from the stack. complexity of O(1) */
void StackPop(stack_t* stack);

/* returns pointer to element at the top of the stack or NULL if invalid pointer was given. complexity of O(1) */
void* StackPeek(const stack_t* stack);

/* returns number of elements in the stack. complexity of O(1) */
size_t StackSize(const stack_t* stack);

/* returns 1 if stack is empty, 0 if not empty and -1 if invalid pointer was given. complexity of O(1) */
int StackIsEmpty(const stack_t* stack);

#endif
