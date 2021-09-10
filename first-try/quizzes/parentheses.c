#include <stdio.h>
#include <string.h>

#include "stack.h"
#include "test_functions.h"

typedef int (*OppFunc_t)(stack_t* stack, char* ch);
int DoNothing(stack_t* stack, char* ch);
int Append(stack_t* stack, char* ch);
int Match(stack_t* stack, char* ch);
int IsValid(char* str, stack_t* stack);

OppFunc_t OppLUT[256] = {0};
char MatchLUT[256] = {0};


void CreateOppLUT()
{
    size_t i = 0;
    
    for (i = 0; i < 256; ++i)
    {
        OppLUT[i] = &DoNothing;
    }

    OppLUT['('] = &Append;
    OppLUT['{'] = &Append;
    OppLUT['['] = &Append;
    OppLUT[')'] = &Match;
    OppLUT['}'] = &Match;
    OppLUT[']'] = &Match;
}

void CreateMatchLUT()
{
    MatchLUT[')'] = '(';
    MatchLUT['}'] = '{';
    MatchLUT[']'] = '[';
}

int DoNothing(stack_t* stack, char* ch)
{
    return 0;
}

int Append(stack_t* stack, char* ch)
{
    StackPush(stack, ch);
    return 0;
}

int Match(stack_t* stack, char* ch)
{
    if (!StackPeek(stack))
    {
        return -1;
    }

	if (*(char*)StackPeek(stack) == MatchLUT[*ch])
	{
		StackPop(stack);
        return 0;
	}pe
    
    return -1;
}

int IsValid(char* str, stack_t* stack)
{
	
	while (*str != '\0')
	{
		if (OppLUT[*str](stack, str))
        {
            return 0;
        }

        str++;
	}

	return StackIsEmpty(stack);
}


int main()
{
    size_t i = 0;
    stack_t* stack;
    char* arr[] = {"}]))[]", "(", "[fd(h)]{}", "(hg{})[]"};

    CreateOppLUT();
    CreateMatchLUT();
 
    for (i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        stack = StackCreate(strlen(arr[i]), 1);
        VerifyInt(IsValid(arr[i], stack), 1, "String");
        StackDestroy(stack);
    }

	return 0;
}










