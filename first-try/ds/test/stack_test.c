#include <stdio.h>

#include "stack.h"
#include "test_functions.h"


int main()
{
    int element1 = 11;
    int element2 = 22;
    int element3 = 33;
    stack_t* my_stack = StackCreate(2, 4);
    
	VerifyInt(StackIsEmpty(my_stack), 1, "IsEmpty"); 
    VerifySizeT(StackSize(my_stack), 0, "Size"); 
    VerifyPointer((void*)StackPeek(my_stack), NULL, "Peek");
    VerifyInt(StackPush(my_stack, &element1), 1, "Push");
	VerifyInt(StackIsEmpty(my_stack), 0, "IsEmpty"); 
    VerifySizeT(StackSize(my_stack), 1, "Size"); 
  	VerifyInt(*(int*)StackPeek(my_stack), 11, "Peek");
    VerifyInt(StackPush(my_stack, &element2), 1, "Push");
    VerifySizeT(StackSize(my_stack), 2, "Size");    
    VerifyInt(*(int*)StackPeek(my_stack), 22, "Peek");
    VerifyInt(StackPush(my_stack, &element3), 0, "Push");
    VerifySizeT(StackSize(my_stack), 2, "Size");
    VerifyInt(*(int*)StackPeek(my_stack), 22, "Peek");
    printf("Pop\n");
    StackPop(my_stack);
	VerifyInt(StackIsEmpty(my_stack), 0, "IsEmpty"); 
    printf("Pop\n");
    StackPop(my_stack);
    printf("Pop\n");
    StackPop(my_stack);
    VerifySizeT(StackSize(my_stack), 0, "Size");
	VerifyInt(StackIsEmpty(my_stack), 1, "IsEmpty");
    printf("Destroy\n");
    StackDestroy(my_stack);
    VerifySizeT(StackSize(my_stack), 0, "Size");
    VerifyInt(StackPush(my_stack, &element3), -1, "Push");
    VerifyPointer((void*)StackPeek(my_stack), NULL, "Peek");
    printf("Destroy\n");
    StackDestroy(my_stack);
    printf("Pop\n");
    StackPop(my_stack);
	VerifyInt(StackIsEmpty(my_stack), -1, "IsEmpty");
    
	VerifyPointer(my_stack = StackCreate(65876575, 876987698769876), NULL, "Create");

    return 0;
}
