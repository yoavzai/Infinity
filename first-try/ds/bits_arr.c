#include <stddef.h>
#include <stdio.h>
#include "bits_arr.h"

#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
#define COUNT_BITS B6(0), B6(1), B6(1), B6(2)

#define SIZE sizeof(bitsarr_t)*8

/*****************************************************/

unsigned char LUT_bits_count[] = {COUNT_BITS};
unsigned char LUT_Mirror[255];

unsigned char Mirror(unsigned char num)
{
	unsigned char new = 0;
	unsigned char mask = 1;

	new |= mask & (num >> 7);
	mask <<= 1;
	new |= mask & (num >> 5);
	mask <<= 1;
	new |= mask & (num >> 3);
	mask <<= 1;
	new |= mask & (num >> 1);
	mask <<= 1;
	new |= mask & (num << 1);
	mask <<= 1;
	new |= mask & (num << 3);
	mask <<= 1;
	new |= mask & (num << 5);
	mask <<= 1;
	new |= mask & (num << 7);

	return new;
}

void InitMirrorLut()
{
	int i = 0;

	for (i = 0; i < 256; ++i)
	{
		LUT_Mirror[i] = Mirror(i);
	}
	
}

/******************************************************/

bitsarr_t BitsArrFlip(bitsarr_t arr, size_t index)
{
	if (index >= SIZE)
	{
		return arr;
	}

	return arr ^ 1UL << index;
}

bitsarr_t BitsArrSetOn(bitsarr_t arr, size_t index)
{
	if (index >= SIZE)
	{
		return arr;
	}

	return arr | 1UL << index;
}

bitsarr_t BitsArrSetOff(bitsarr_t arr, size_t index)
{
	if (index >= SIZE)
	{
		return arr;
	}

	return 	arr & (~0UL ^ (1UL << index));
}

size_t BitsArrCountOn(bitsarr_t arr)
{
	size_t counter = 0;
	bitsarr_t mask = 1;

	while (mask)
	{
		if (mask & arr)
		{
			++counter;
		}

		mask <<= 1;
	}

	return counter;
}

size_t BitsArrCountOnLut(bitsarr_t arr)
{
	size_t sum = 0;

	while (arr)
	{
		sum += LUT_bits_count[(unsigned char)arr];

		arr >>= SIZE / 8;
	}
	
	return sum;
}

size_t BitsArrCountOff(bitsarr_t arr)
{
	size_t counter = 0;
	bitsarr_t mask = 1;

	while (mask)
	{
		if (mask & arr)
		{
			++counter;
		}

		mask <<= 1;
	}

	return SIZE - counter;
}

bitsarr_t BitsArrResetAll(bitsarr_t arr)
{
	return (arr & 0UL);
}

bitsarr_t BitsArrSetAll(bitsarr_t arr)
{
	return (arr | ~0UL);
}

int BitsArrIsOn(bitsarr_t arr, size_t index)
{
	if (index >= SIZE)
	{
		return -1;
	}

	return (arr & (1UL << index)) ? 1 : 0;
}

int BitsArrIsOff(bitsarr_t arr, size_t index)
{
	if (index >= SIZE)
	{
		return -1;
	}
	
	return (arr & (1UL << index)) ? 0 : 1;
}

bitsarr_t BitsArrRotR(bitsarr_t arr, size_t n)
{
	n %= SIZE;	
	
	return (arr >> n | arr << (SIZE - n));
}

bitsarr_t BitsArrRotL(bitsarr_t arr, size_t n)
{
	n %= SIZE;

	return (arr << n | arr >> (SIZE - n));
}

char* BitsArrToString(bitsarr_t arr, char *dest)
{
	size_t i = 0;
	bitsarr_t mask = 1UL << (SIZE - 1);

	while (mask)
	{
		if (mask & arr)
		{
			dest[i] = '1';
		}
	
		else 
		{
			dest[i] = '0';
		}
	
		mask >>= 1;
		++i;
	}

	dest[i] = '\0';

	return dest;
}

bitsarr_t BitsArrMirror(bitsarr_t arr)
{
	size_t shift = SIZE - 1;
	bitsarr_t new = 0;
	bitsarr_t mask_start = 1;
	bitsarr_t mask_end = 1;
	mask_end <<= (SIZE - 1);

	while (mask_end > mask_start)
	{
		
		new |= ((mask_start & arr) << shift);
		new |= ((mask_end & arr) >> shift);
		
		shift -=2;
		mask_start <<= 1;
		mask_end >>= 1;
	}

	return new;
}

bitsarr_t BitsArrMirrorLut(bitsarr_t arr)
{
	size_t i = 0;
	static char was_init = 0;
	bitsarr_t mirror = 0;

	if (!was_init)
	{
		InitMirrorLut();
		was_init = 1;
	}
	
	for (i = 0; i < SIZE / 8; ++i)
	{
        mirror <<= SIZE / 8;
    
        mirror |= (bitsarr_t)LUT_Mirror[(unsigned char)arr];
	
		arr >>= SIZE / 8;
	}
	
	return mirror;
}

bitsarr_t BitsArrSetBit(bitsarr_t arr, size_t index, int state)
{
	if (index >= SIZE || (state != 1 && state != 0))
	{
		return arr;
	}
	
	arr &= ~(1UL << index);
	arr |= ((bitsarr_t)state << index);

	return arr;
}

