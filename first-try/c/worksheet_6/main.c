#include <stdio.h>
#include "exercise.h"


void Pow2Test()
{
	unsigned int x = 0, y = 5;
	printf("Pow2:\n");
	
	for (; x <= y; x++)
	{
		printf("%ld\n", Pow2(x, y));
	}
}

void IsPow2Test()
{
	unsigned int x = 2;
	printf("\nIsPow2Loop:\n");
	printf("%d\n", IsPow2Loop(x));
	printf("\nIsPow2:\n");
	printf("%d\n", IsPow2(x));
}

void AddOneTest()
{
	unsigned int a = 0;
	printf("\nAddOne:\n");
	printf("%u\n", AddOne(a));
}

void ThreeBitsOnTest()
{
	unsigned int arr[] = {324, 11, 3, 7, 0, 14};
	printf("\nThreeBitsOn:\n");
	ThreeBitsOn(arr, sizeof(arr) / sizeof(arr[0]));
}

void MirrorTest()
{
	unsigned char num = 1;
	
	printf("\nMirror:\n");
	PrintUnsignedchar(num);
	PrintUnsignedchar(Mirror(num));

}

void Bit6And2Test()
{
	unsigned char num = 2;

	printf("\nBit6And2:\n");
	printf("%i\n",Bit6And2(num));
}

void Bit6Or2Test()
{
	unsigned char num = 2;

	printf("\nBit6Or2:\n");
	printf("%i\n",Bit6Or2(num));
}

void SwapBits3And5Test()
{
	unsigned char num = 12;

	printf("\nSwapBits3And5:\n");
	PrintUnsignedchar(num);
	PrintUnsignedchar(SwapBits3And5(num));
}

void Closest16Test()
{
	unsigned int num = 48;

	printf("\nClosest16:\n");
	printf("%u\n",Closest16(num));
}

void SwapTest()
{
	int x = 4, y = -3;

	printf("\nSwap:\n");
	printf("%i  %i\n", x, y);
	Swap(&x, &y);
	printf("%i  %i\n", x, y);
}

void CountSetBitsTest()
{
	int num = -534;
	printf("\nCountSetBitsLoop:\n");
	PrintUnsignedInt(num);
	printf("%u\n", CountSetBitsLoop(num));
	printf("\nCountSetBits:\n");
	printf("%u\n", CountSetBits(num));
}

void PrintFloatTest()
{
	float num = 234.4;

	printf("\nPrintFloat:\n");
	PrintFloat((unsigned int*)&num);
}

int main()
{
	Pow2Test();
	IsPow2Test();
	AddOneTest();
	ThreeBitsOnTest();
	MirrorTest();
	Bit6And2Test();
	Bit6Or2Test();
	SwapBits3And5Test();
	Closest16Test();
	SwapTest();
	CountSetBitsTest();
	PrintFloatTest();

	return 0;
}
