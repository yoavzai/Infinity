#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <string.h> /* strcmp */

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"

void VerifySizeT(size_t result, size_t expected, char* name)
{
	if (result == expected)
	{
		printf(GREEN"%s SUCCESS\n",name);
	}
	else
	{
		printf(RED"%s FAIL\n",name);
	}
}

void VerifySizeTNot(size_t result, size_t expected, char* name)
{
	if (result != expected)
	{
		printf(GREEN"%s SUCCESS\n",name);
	}
	else
	{
		printf(RED"%s FAIL\n",name);
	}
}

void VerifyInt(int result, int expected, char* name)
{
	if (result == expected)
	{
		printf(GREEN"%s SUCCESS\n",name);
	}
	else
	{
		printf(RED"%s FAIL\n",name);
	}
}

void VerifyIntNot(int result, int expected, char* name)
{
	if (result != expected)
	{
		printf(GREEN"%s SUCCESS\n",name);
	}
	else
	{
		printf(RED"%s FAIL\n",name);
	}
}

void VerifyString(char* result, char* expected, char* name)
{
	if (!(strcmp(result, expected)))
	{
		printf(GREEN"%s SUCCESS\n",name);
	}
	else
	{
		printf(RED"%s FAIL\n",name);
	}
}

void VerifyPointer(void* result, void* expected, char* name)
{
	if (result == expected)
	{
		printf(GREEN"%s SUCCESS\n",name);
	}
	else
	{
		printf(RED"%s FAIL\n",name);
	}
}

void VerifyPointerNot(void* result, void* expected, char* name)
{
	if (result != expected)
	{
		printf(GREEN"%s SUCCESS\n",name);
	}
	else
	{
		printf(RED"%s FAIL\n",name);
	}
}









