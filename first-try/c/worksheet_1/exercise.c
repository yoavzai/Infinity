#include <stdio.h>

void PrintHello()
{
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",0x22,0x48,0x65,0x6c,0x6c,0x6F,0x20,0x57,0x6F,0x72,0x6c,0x64,0x21,0x22,0xA);
}

double Power(int exponent)
{
	double result = 1, base = 10;
	if (0 > exponent)
	{
		base = 0.1;
		exponent *= -1;
	}
	while (0 != exponent)
	{
		result *= base;
		exponent--;
	}	
	return result;
}

int flip(int num)
{
	int flipped = 0;
	while (0 != num)
	{
		flipped *= 10;
		flipped += num % 10;
		num /= 10;
	}
	return flipped;
}

void swap(int* a_p, int* b_p)
{
	int temp = *a_p;
	*a_p = *b_p;
	*b_p = temp;
}

int main()
{
	int exponent, to_be_flipped, a, b;
	/* 1 */
	PrintHello();
	/* 2 */
	printf("Enter an exponent: ");
	scanf("%d", &exponent);
	printf("10^%d = %f\n", exponent, Power(exponent));
	/* 3 */
	printf("Enter an integer to be flipped: ");
	scanf("%d", &to_be_flipped);
	printf("%d ---> %d\n", to_be_flipped, flip(to_be_flipped));
	/* 4 */
	printf("Enter an integer: ");
	scanf("%d", &a);
	printf("Enter another integer: ");
	scanf("%d", &b);
	printf("Before swap:\n");
	printf("Adress: %p  Value: %d\n", &a, a);
	printf("Adress: %p  Value: %d\n", &b, b);
	swap(&a, &b);
	printf("After swap:\n");
	printf("Adress: %p  Value: %d\n", &a, a);
	printf("Adress: %p  Value: %d\n", &b, b);
	return 0;
}
