#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#include "funcs.h"
#include "exercise.h"

#define WORD_SIZE sizeof(size_t)

/**********************************************************/

void* Memset(void* dest_p, int data, size_t num_bytes)
{
	char byte_data = (char)data;
	char* tail_p = (char*)dest_p;
	size_t word_data = CreateWordForMemset(byte_data);
	size_t* body_p = NULL;

	/* tail_size is the smaller between: (number of bytes until next alignment | number of bytes to set) */
	int tail_size = Min((WORD_SIZE - ((size_t)dest_p % WORD_SIZE)) % WORD_SIZE, num_bytes);

	while (0 < tail_size)
	{
		*tail_p = byte_data;

		--tail_size;
		--num_bytes;
		++tail_p;
	}
	
	body_p = (size_t*)tail_p;

	while (num_bytes >= WORD_SIZE)
	{
		*body_p = word_data;
		
		num_bytes -= WORD_SIZE;
		++body_p;
	}

	tail_p = (char*)body_p;

	while (0 < num_bytes)
	{
		*tail_p = byte_data;

		--num_bytes;
		++tail_p;
	}

	return dest_p;	
}

void* Memcpy(void* dest_p, const void* src_p, size_t num_bytes)
{
	char* source_p = (char*) src_p;
	char* dest_tail_p = (char*)dest_p;
	size_t* dest_body_p = NULL;
	
	/* dest_tail_size is the smaller between: (number of bytes until next alignment | number of bytes to set) */
	int dest_tail_size = Min((WORD_SIZE - ((size_t)dest_p % WORD_SIZE)) % WORD_SIZE, num_bytes);
	int source_offset = 0;

	while (0 < dest_tail_size)
	{
		*dest_tail_p = *source_p;
		
		--num_bytes;
		--dest_tail_size;
		++dest_tail_p;
		++source_p;
	}
	
	dest_body_p = (size_t*)dest_tail_p;
	source_offset = (size_t)source_p % WORD_SIZE;

	while (num_bytes >= WORD_SIZE)
	{
		*dest_body_p = CreateWordForMemcpy((size_t*)(source_p - source_offset), source_offset);
		
		num_bytes -= WORD_SIZE;
		source_p += WORD_SIZE;
		++dest_body_p;
	}

	dest_tail_p = (char*)dest_body_p;

	while (0 < num_bytes)
	{
		*dest_tail_p = *source_p;

		--num_bytes;
		++dest_tail_p;
		++source_p;
	}

	return dest_p;	
}

void* Memmove(void* dest_p, const void* src_p, size_t num_bytes)
{
	ptrdiff_t diff = (char*)dest_p - (char*)src_p;

	if (num_bytes <= (size_t)diff || 0 > diff)
	{
		Memcpy(dest_p, src_p, num_bytes);
		
		return dest_p;
	}
	
	Memcpy((void*)((char*)dest_p + diff), dest_p, num_bytes - diff);
	Memcpy(dest_p, src_p, diff);

	return dest_p;
}


char* Itoa(int num, char* buffer)
{
	int i = 0;
	char negative = 0;
	
	if (num < 0)
	{
		negative = 1;
		num *= -1;
	}

	while (num != 0)
	{
		buffer[i] = (num % 10) + '0';
		num /= 10;
		++i;
	}
	
	if (negative)
	{
		buffer[i] = '-';
		++i;
	}

	buffer[i] = '\0';

	return ReverseString(buffer);
}

int Atoi(char* str, int base) 
{ 
	int i = 0;
    int res = 0;
    int sign = 1;
	char* end = str + strlen(str) - 1;
  
    if (str[0] == '-')
	{ 
        sign = -1; 
        str++;
    } 
  
    while (end >= str)
	{
		res += CharToInt(*end) * pow(base, i);
		end--;
		i++;
	}
    
    return sign * res; 
} 

void PrintUnique(char* str1, char* str2, char* str3)
{
	int i = 0;
	int lut1[256] = {0};
	int lut2[256] = {0};
	int lut3[256] = {0};

	while (*str1 != '\0')
	{
		lut1[(int)*str1] = 1;
		str1++;
	}

	while (*str2 != '\0')
	{
		lut2[(int)*str2] = 1;
		str2++;
	}

	while (*str3 != '\0')
	{
		lut3[(int)*str3] = 1;
		str3++;
	}

	for (i = 0; i < 256; ++i)
	{
		if (lut1[i] && lut2[i] && !lut3[i])
		{
			printf("%c", i);
		}
	}
	puts("");
}

void WhichEndian()
{
	unsigned int i = 1; 
   	char* c = (char*)&i; 
   	if (*c)     
		printf("Little endian\n"); 
   	else
       	printf("Big endian\n");
}


























