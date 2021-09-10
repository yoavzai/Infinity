#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>

#include "Poly.h"

/* Allocation Functions */
char* SetString(char* dest, const void* source)
{
	dest = malloc(strlen(source) + 1);

	if (dest == NULL)
	{
		fprintf(stderr, "Error allocating memory: %s\n", strerror(errno));
		exit(1);
	}
	
	strcpy(dest, source);

	return dest;
}

char* AddIntToStr(char* dest, int source)
{
	char int_str[20];
	sprintf(int_str, "%d", source);

	dest = realloc(dest, strlen(dest) + strlen(int_str) + 1);
	
	if (dest == NULL)
	{
		fprintf(stderr, "Error allocating memory: %s\n", strerror(errno));
		exit(1);
	}

	strcat(dest, int_str);
	
	return dest;
}

/* Set Value*/
void PolySetValue(Data_t* elem, enum data_type_t set_type, const void* value_p)
{
	(*elem).type = set_type;
	
	switch ((*elem).type)
	{
		case TYPE_INT:
			(*elem).value.d = *(const int*)value_p;
			break;

		case TYPE_FLOAT:
			(*elem).value.f = *(const float*)value_p;
			break;
		
		case TYPE_STR:
			(*elem).value.str = SetString((*elem).value.str, value_p);
			break;
		
		default:
			;
	}
}

/* Add Int */
void PolyAdd(Data_t* elem, int num)
{
	switch ((*elem).type)
	{
		case TYPE_INT:
			(*elem).value.d += num;
			break;

		case TYPE_FLOAT:
			(*elem).value.f += num;
			break;
		
		case TYPE_STR:
			(*elem).value.str = AddIntToStr((*elem).value.str, num);

		default:
			;
	}
}

/* Print Single */
void PolyPrintSingle(Data_t* elem)
{
		switch ((*elem).type)
	{
		case TYPE_INT:
			printf("%d\n", (*elem).value.d);
			break;

		case TYPE_FLOAT:
			printf("%f\n", (*elem).value.f);
			break;
		
		case TYPE_STR:
			printf("%s\n", (*elem).value.str);

		default:
			;
	}
}

/* Print All */
void PolyPrintAll(Data_t* elem, size_t size)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		PolyPrintSingle(&elem[i]);
	}
}

/* Clean Single */
void PolyCleanSingle(Data_t* elem)
{
	switch ((*elem).type)
	{
		case TYPE_STR:
			free((*elem).value.str);
			break;

		default:
			;
	}
	
	(*elem).type = TYPE_EMPTY;	
}

/* Clean All */
void PolyCleanAll(Data_t* elem, size_t size)
{
	size_t i = 0;
	
	for (i = 0; i < size; ++i)
	{
		PolyCleanSingle(&elem[i]);
	}
}



























