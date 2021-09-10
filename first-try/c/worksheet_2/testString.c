#include <stdio.h>
#include <stdlib.h> /* malloc */
#include "String.h"
#define SIZE 100

void StrlenTest()
{
	char str[SIZE];
	printf("Choose a word: ");
	gets(str);
	printf("Word length is %lu\n", Strlen(str));
	printf("------------------------\n");

}

void StrcmpTest()
{
	char str1[SIZE], str2[SIZE];
	printf("Choose first word: ");
	gets(str1);
	printf("Choose second word: ");
	gets(str2);
	printf("%d\n", Strcmp(str1, str2));
	printf("-------------------------\n");
}

void StrcpyTest()
{
	char source[SIZE], copy[SIZE];
	printf("Choose a word: ");
	gets(source);
	Strcpy(copy, source);
	printf("%s --> %p\n", source, source);
	printf("%s --> %p\n", copy, copy);
	printf("-------------------------\n");
}

void StrncpyTest()
{
	char source[SIZE], copy[SIZE];
	size_t num = 0;
	printf("Choose a word: ");
	gets(source);
	printf("Choose a number: ");
	scanf("%lu", &num);
	Strncpy(copy, source, num);
	printf("%s --> %p\n", source, source);
	printf("%s --> %p\n", copy, copy);
	printf("-------------------------\n");
}

void StrcasecmpTest()
{
	char str1[SIZE], str2[SIZE];
	printf("Choose a word: ");
	gets(str1);
	printf("Choose a word: ");
	gets(str2);
	printf("%d\n", Strcasecmp(str1, str2));
	printf("-------------------------\n");
}

void StrchrTest()
{
	char word[SIZE], letter;
	printf("Choose a word: ");
	gets(word);
	printf("Choose a letter: ");
	scanf("%c", &letter);
	printf("%s --> %p\n", word, word);
	printf("%c --> %p\n", letter, Strchr(word, letter));
	printf("-------------------------\n");
}

void StrdupTest()
{
	char source[SIZE];
	char* dup;
	printf("Choose a word: ");
	gets(source);
	dup = Strdup(source);
	printf("%s at %p\n", source, source);
	printf("%s at %p\n", dup, dup);
	printf("-------------------------\n");
}

void StrcatTest()
{
	char str1[SIZE], str2[SIZE];
	printf("Choose a word: ");
	gets(str1);
	printf("Choose a word: ");
	gets(str2);
	Strcat(str1, str2);
	printf("%s\n", str1);
	printf("-------------------------\n");
}

void StrncatTest()
{
	char str1[SIZE], str2[SIZE];
	size_t num;
	printf("Choose a word: ");
	gets(str1);
	printf("Choose a word: ");
	gets(str2);
	printf("Choose a number: ");
	scanf("%lu", &num);
	Strncat(str1, str2, num);
	printf("%s\n", str1);
	printf("-------------------------\n");
}

void StrstrTest()
{
	char str1[SIZE], str2[SIZE];
	printf("Choose a haystack: ");
	gets(str1);
	printf("Choose a needle: ");
	gets(str2);
	printf("%s --> %p\n", str1, str1);
	printf("%s --> %p\n", str2, Strstr(str1, str2));
	printf("-------------------------\n");
}

void StrspnTest()
{
	char str1[SIZE], str2[SIZE];
	printf("Choose a word: ");
	gets(str1);
	printf("Choose a source: ");
	gets(str2);
	printf("The first %lu characters of \"%s\" are found in \"%s\"\n", Strspn(str1, str2), str1, str2);
	printf("-------------------------\n");
}

void StrtokTest()
{
	char str1[SIZE], str2[SIZE], *temp;
	printf("Choose a word: ");
	gets(str1);
	printf("Choose delimiters: ");
	gets(str2);
	if (!Strcmp(str1, "NULL"))
	{
		printf("%s\n", Strtok(NULL, str2));
		printf("-------------------------\n");
	}
	else
	{
		printf("%s\n", Strtok(str1, str2));
		printf("-------------------------\n");
	}
	
}

void IsPalindromeTest()
{
	char str[SIZE];
	printf("Choose a word: ");
	gets(str);
	if(IsPalindrome(str))
	{
		printf("The word IS a palindrome!\n");
		printf("-------------------------\n");
	}
	else
	{
		printf("The word IS NOT a palindrome!\n");
		printf("-------------------------\n");
	}
}

void SevenBoomTest()
{
	int from, to;
	printf("from: ");
	scanf("%d", &from);
	printf("to: ");
	scanf("%d", &to);
	SevenBoom(from, to);
	printf("\n-------------------------\n");
}

void SwapPtrsTest()
{
	int x, y;
	int* ptr_to_x = &x;
	int* ptr_to_y = &y;
	printf("Choose a number for x: ");
	scanf("%d", ptr_to_x);
	printf("Choose a number for y: ");
	scanf("%d", ptr_to_y);
	printf("\n");
	printf("Before: \n");
	printf("x --> value: %d, adress: %p\n", x, &x);
	printf("y --> value: %d, adress: %p\n", y, &y);
	printf("ptr_to_x --> value: %p, adress: %p\n", ptr_to_x, &ptr_to_x);
	printf("ptr_to_y --> value: %p, adress: %p\n\n", ptr_to_y, &ptr_to_y);
	SwapPtrs(&ptr_to_x, &ptr_to_y);
	printf("After: \n");
	printf("x --> value: %d, adress: %p\n", x, &x);
	printf("y --> value: %d, adress: %p\n", y, &y);
	printf("ptr_to_x --> value: %p, adress: %p\n", ptr_to_x, &ptr_to_x);
	printf("ptr_to_y --> value: %p, adress: %p\n", ptr_to_y, &ptr_to_y);
	printf("-------------------------\n");
}

void RmSpacesTest()
{
	char str[SIZE];
	printf("Choose a word: ");
	gets(str);
	printf("\nBefore: \n");
	printf("|%s|\n", str);
	RmSpaces(str);
	printf("\nAfter: \n");
	printf("|%s|\n", str);
	printf("-------------------------\n");
}


void SumBigNumsTest()
{
	char str1[SIZE], str2[SIZE];
	printf("Choose a big number: ");
	gets(str1);
	printf("Choose another big number: ");
	gets(str2);
	printf("The sum is %s\n", SumBigNums(str1, str2));
}


int main()
{
	int test_num = 0, exit_button = 1;
	while (exit_button)
	{
		printf("1) Strlen\n");
		printf("2) Strcmp\n");
		printf("3) Strcpy\n");
		printf("4) Strncpy\n");
		printf("5) Strcasecmp\n");
		printf("6) Strchr\n");
		printf("7) Strdup\n");
		printf("8) Strcat\n");
		printf("9) Strncat\n");
		printf("10) Strstr\n");
		printf("11) Strspn\n");
		printf("12) Strtok\n");
		printf("13) IsPalindrome\n");
		printf("14) SevenBoom\n");
		printf("15) SwapPtrs\n");
		printf("16) RmSpaces\n");
		printf("17) SumBigNums\n");
		printf("18) EXIT\n");
		printf("Choose a test: ");
		scanf("%d", &test_num);
		getchar();

		switch (test_num)
		{
			case 1:
				StrlenTest();
				break;
			case 2:
				StrcmpTest();
				break;
			case 3:
				StrcpyTest();
				break;
			case 4:
				StrncpyTest();
				break;
			case 5:
				StrcasecmpTest();
				break;
			case 6:
				StrchrTest();
				break;
			case 7:
				StrdupTest();
				break;
			case 8:
				StrcatTest();
				break;
			case 9:
				StrncatTest();
				break;
			case 10: 
				StrstrTest();
				break;
			case 11:
				StrspnTest();
				break;
			case 12:
				StrtokTest();
				break;
			case 13:
				IsPalindromeTest();
				break;
			case 14:
				SevenBoomTest();
				break;
			case 15:
				SwapPtrsTest();
				break;
			case 16:
				RmSpacesTest();
				break;
			case 17:
				SumBigNumsTest();
				break;
			case 18:
				exit_button = 0;
		}	

	}

	return 0;
}


