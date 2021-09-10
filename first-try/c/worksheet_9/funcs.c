#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#include "funcs.h"

#define WORD_SIZE sizeof(size_t)

size_t CreateWordForMemset(char byte)
{
	size_t word = 0;
	size_t mask = byte;
	int word_size = sizeof(size_t);
	
	while (mask)
	{
		word |= mask;
		mask <<= word_size;
	}

	return word;
}

int Min(size_t x, size_t y)
{
	return ((x < y) ? x : y);
}

size_t CreateWordForMemcpy(size_t* src_p, int offset)
{
	size_t word = 0;
	
	word |= *src_p >> (offset * 8);

	if (offset != 0)
	{
		word |= *(src_p + 1) << ((WORD_SIZE - offset) * 8);
	}

	return word;
}

char* ReverseString(char* str)
{
	int len = strlen(str);
	int i = 0;
	char temp = 0;

	while (len - 1 > i)
	{
		temp = str[i];
		str[i] = str[len - 1];
		str[len - 1] = temp;

		--len;
		++i;
	}

	return str;
}

int CharToInt(char ch)
{
	if (isalpha(ch))
	{
		return toupper(ch) - 'A' + 10;
	}

	return ch - '0';
}




















