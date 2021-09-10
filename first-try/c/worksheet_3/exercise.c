#include <stdio.h> /* printf */
#include <stdlib.h> /* calloc, malloc */
#include <stddef.h> /* size_t */
#include <string.h> /* strlen */
#include <math.h> /* pow() */
#include "funcs.h"
#define BIT(x) sizeof(x)*8 /* gives the size in bits */

/*
char** CpyArrOfStr(const char** source)
{
	size_t copy_len = sourceLen(source), i = 0;
	char** copy;
	char* word;
	copy = calloc(copy_len + 1, sizeof(*source));	
	
	for(; copy_len > i; ++i)
	{
		word = malloc(strlen(*(source + i)) + 1);
		StrCpyToLower(word, *(source + i));
		*(copy + i) = word;		
	}
	
	*(source + i) = NULL;

	return copy;
}
*/

char** CpyArrOfStr(const char** source)
{
	size_t i = 0, menu_size = 0, content_size = 0;
	char** menu = NULL;
	char* content = NULL;
	
	for (; source[i]; ++i)
	{
		++menu_size;
		content_size += strlen(source[i]) + 1;
	}
	++menu_size;

	menu = malloc((menu_size * (*menu)) + content_size);
	if (menu == NULL)
	{
		fprintf(stderr, "Out of memory\n")
		exit(1);
	}

	content = (char*)(menu + menu_size);

	for (i = 0; source[i]; ++i)
	{
		menu[i] = content;
		content = StrCpyToLower(content, source[i]); /* returns a pointer
													 to the end of the current string*/		
		++content;
	}
	
	menu[i] = NULL;
	
	return menu;
}

void PrintArrOfStr(const char** source)
{
	while (*source)
	{
		printf("%s\n", *source);
		++source;	
	}
}

/*
void FreeBuffer(char** buffer)
{
	size_t i = 0;

	for (; *(buffer + i); ++i)
	{
		free(*(buffer+i));
	}
	
	free(buffer);
}
*/

size_t Josephus(char* source)
{
	int sowrd = 0;
	size_t size = StrToSizet(source), i = 0, dead_count = 0;
	char* group = calloc(size, 1); /* init all to 0 meaning alive */
	
	while (1)
	{
		i %= size;

		if (!group[i]) /* live soldier */
		{	
			if (dead_count == (size - 1)) /* last soldier */
			{
				free(group);
				return i;
			}

			else if (sowrd)
			{
				group[i] = 'd'; /* now he's dead */
				++dead_count;
				sowrd = 0;
			}

			else
			{
				sowrd = 1;
			}
		}

		++i;
	}	
}

void PrintTypes()
{
	printf("char: %lu byte\n", sizeof(signed char));
	printf("%d  to  %d\n", (int)-pow(2, BIT(signed char) - 1), (int)pow(2, BIT(signed char) - 1) - 1);
	printf("%hx  to  %x\n", (int)-pow(2, BIT(signed char) - 1) & 0xff, (int)pow(2, BIT(signed char) - 1) - 1);
	printf("\nunsigned char: %lu byte\n", sizeof(char));
	printf("0  to  %d\n", (int)(pow(2, BIT(signed char)) - 1));
	printf("0  to  %x\n", (int)(pow(2, BIT(signed char)) - 1));

	printf("\nshort: %lu bytes\n", sizeof(short));
	printf("%d  to  %d\n", (int)-pow(2, BIT(short) - 1), (int)pow(2, BIT(short) - 1) - 1);
	printf("%hx  to  %hx\n", (int)-pow(2, BIT(short) - 1), (int)pow(2, BIT(short) - 1) - 1);
	printf("\nunsigned short: %lu bytes\n", sizeof(unsigned short));
	printf("0  to  %d\n", (int)(pow(2, BIT(unsigned short)) - 1));
	printf("0  to  %x\n", (int)(pow(2, BIT(unsigned short)) - 1));

	printf("\nint: %lu bytes\n", sizeof(int));
	printf("%d  to  %u\n", (int)-pow(2, BIT(int) - 1), (unsigned int)pow(2, BIT(int) - 1) - 1);
	printf("%x  to  %x\n", (int)-pow(2, BIT(int) - 1), (unsigned int)pow(2, BIT(int) - 1) - 1);
	printf("\nunsigned int: %lu bytes\n", sizeof(unsigned int));
	printf("0  to  %u\n", (unsigned int)(pow(2, BIT(unsigned int)) - 1));
	printf("0  to  %x\n", (unsigned int)(pow(2, BIT(unsigned int)) - 1));

	printf("\nlong: %lu bytes\n", sizeof(long));
	printf("%ld  to  %lu\n", (long)-pow(2, BIT(long) - 1), (unsigned long)pow(2, BIT(long) - 1) - 1);
	printf("%lx  to  %lx\n", (long)-pow(2, BIT(long) - 1), (unsigned long)pow(2, BIT(long) - 1) - 1);
	printf("\nunsigned long: %lu bytes\n", sizeof(unsigned long));
	printf("0  to  %lu\n", (unsigned long)(pow(2, BIT(unsigned long)) - 1));
	printf("0  to  %lx\n", (unsigned long)(pow(2, BIT(unsigned long)) - 1));

}

