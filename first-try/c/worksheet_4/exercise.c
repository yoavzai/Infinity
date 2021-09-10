#include <stdio.h>
#include <stdlib.h>

void PrintNone()
{
}

void PrintA()
{
	printf("A pressed\n");
}

void PrintT()
{
	printf("T pressed\n");
}

void PrintEsc()
{
	system("stty icanon echo");

	exit(1);
}

int main()
{
	int i;
	char c;
	void (*print_p[256])();

	for (; i < 256; i++)
	{
		print_p[i] = &PrintNone;
	}

	print_p[65] = &PrintA;
	print_p[84] = &PrintT;
	print_p[27] = &PrintEsc;

	system("stty -icanon -echo");	

	while (1)
	{
		scanf("%c", &c);
		print_p[(unsigned int)c]();
	}

	system("stty icanon echo");
	
	return 0;
}
