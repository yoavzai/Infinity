#include <stdio.h> /* size_t, sprintf */

int FlipVal(int num)
{
	int reversed = 0;
	int sign = 1;

	if (num < 0)
	{
		num *= -1;
		sign = -1;
	}

	while (num != 0)
	{
		reversed *= 10;
		reversed += num % 10;
		num /= 10;
	}

	return reversed * sign;
}

unsigned char Mirror (unsigned char byte)
{
	unsigned char mirrored = 0;
	size_t i = 0;

	for (i = 0; i < 8; ++i)
	{
		mirrored |= (1 & (byte>>i))<<(7 - i);
	}

	return mirrored;
}

int Flip (int val, int n)
{
	return (val ^ 1<<n);
}

size_t CountOn(unsigned char byte)
{
	size_t counter = 0;
	size_t i = 0;

	for (i = 0; i < 8; ++i)
	{
		counter += (((byte>>i) & 1) == 1);
	}

	return counter;
}

char RotateLeft(char byte, int nbits)
{
	nbits %= 8;

	return ((unsigned char)byte<<nbits |
 			(unsigned char)byte>>(8 - nbits));
}

void SwapPtr(int** ptr1, int** ptr2)
{
	int* temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

size_t Strlen(const char* s)
{
	size_t counter = 0;

	while (*s != '\0')
	{
		counter++;
		s++;
	}

	return counter;
}

int Strcmp(const char* s1, const char* s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return *s1 - *s2;
}

char* Strcpy(char* dest, const char* src)
{
	size_t i = 0;
	size_t len = Strlen(src);
	
	for (i = 0; i <= len; ++i)
	{
		dest[i] = src[i];
	}

	return dest;
}

char* Strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
    	dest[i] = src[i];
	}

	while (i < n)
	{    
		dest[i] = '\0';
		++i;
	}

    return dest;
}

char* Strcat(char* dest, const char* src)
{
	size_t len = Strlen(dest);

	return Strcpy(dest + len, src);
}

long Fibonacci(unsigned int n)
{
	long temp = 0;
	long previous = 0;
	long current = 1;

	while (n > 1)
	{
		temp = current;
		current += previous;
		previous = temp;
		--n;
	}

	return current;
}

void IntToString(char* dest, int num)
{
	sprintf(dest, "%d", num);
}

int MultByEight(int num)
{
	return num<<3;
}

int main()
{
	return 0;
}










