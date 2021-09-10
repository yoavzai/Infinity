#include <stdio.h>
#include <math.h>
#include <stddef.h>
#include "exercise.h"
#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
#define COUNT_BITS B6(0), B6(1), B6(1), B6(2)


int CountSetBits2(unsigned int num)
{
	int counter = 0;
	unsigned int mask = 1;

	for (; mask != 0; mask <<= 1)
	{
		if (num & mask)
		{
			++counter;
		}
	}

	return counter;
}

void PrintUnsignedInt(unsigned int num)
{
	unsigned int mask = 0x80000000;
	while (mask)
	{
		if (mask & num)
		{
			printf("%d", 1);
		}
		else
		{
			printf("%d", 0);
		}
		mask >>= 1;
	}
	printf("\n");
}

void PrintUnsignedchar(unsigned char num)
{
	unsigned char mask = 0x80;

	while (mask)
	{
		if (mask & num)
		{
			printf("%d", 1);
		}
		else
		{
			printf("%d", 0);
		}
		mask >>= 1;
	}
	printf("\n");
}

/*************************************/
/*************************************/

long Pow2(unsigned int x, unsigned int y)
{
	return (x << y);
}

/*************************************/

int IsPow2Loop(unsigned int num)
{
	return (CountSetBits2(num) == 1 && num != 1);
}

int IsPow2(unsigned int num)
{
	return (!(num & (num - 1)) && 1 < num);
}

/*************************************/

unsigned int AddOne(unsigned int num)
{
	unsigned int mask = 1;
	
	while (mask != 0)
	{
		if (!(num & mask))
		{
			num ^= mask;
			return num;
		}
		
		num ^= mask;
		num <<= 1;		
	}
	
	/* if the number is all ones */
	return 0;
}

/*************************************/

void ThreeBitsOn(unsigned int* arr, size_t len)
{
	size_t i = 0;

	for (i = 0; i < len; ++i)
	{
		if (CountSetBits2(arr[i]) == 3)
		{
			printf("%u\n", arr[i]);
		}	
	}	
}

/*************************************/

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

/*************************************/

int Bit6And2(unsigned char num)
{
	return ((num & 0x2) && (num & 0x20));
}

/*************************************/

int Bit6Or2(unsigned char num)
{
	return ((num & 0x2) || (num & 0x20));
}

/*************************************/

unsigned char SwapBits3And5(unsigned char num)
{
	unsigned char mask1 = 0x4;
	unsigned char mask2 = 0x10;
	unsigned char zeroer = 0xeb;

	mask1 &= num;
	mask2 &= num;
	num &= zeroer;

	mask1 <<= 2;
	mask2 >>= 2;
	mask1 |= mask2;

	num |= mask1;

	return num;
}

/*************************************/

unsigned int Closest16(unsigned int num)
{
	unsigned int mask = 0xfffffff0;
	return (num & mask);
}

/*************************************/

void Swap(int* x, int* y)
{
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
}

/*************************************/

unsigned int CountSetBitsLoop(int num)
{
	size_t counter = 0;
	unsigned int mask = 0x80000000;
	
	while (mask)
	{
		if (mask & num)
		{
			++counter;
		}
		
		mask >>= 1;
	}
	
	return counter;
}

unsigned int CountSetBits(int num)
{
	unsigned int lookup[256] = {COUNT_BITS};
	unsigned int mask = 0xff, byte1, byte2, byte3, byte4;
	byte1 = num & mask;
	byte2 = (num >> 8) & mask;
	byte3 = (num >> 16) & mask;
	byte4 = (num >> 24) & mask;
		
	return (lookup[byte1] + lookup[byte2] + lookup[byte3] + lookup[byte4]);
}

/*************************************/

void PrintFloat(unsigned int* num)
{
	unsigned int mask = 0x80000000;
	while (mask)
	{
		if (mask & *num)
		{
			printf("%d", 1);
		}
		else
		{
			printf("%d", 0);
		}
		mask >>= 1;
	}
	printf("\n");
}

/*************************************/
/*************************************/























