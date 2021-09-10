#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <stdio.h> /* printf */

size_t Strlen(const char* str)
{
	size_t i = 0;

	while (*(str+i) != '\0')
	{
		i++;
	}
	return i;
}

int Strcmp(const char* str1, const char* str2)
{

	while (*str1 == *str2 && (*str1 || *str2))
	{
		str1++;
		str2++;
	}
	
	return (*str1 - *str2);

}

char* Strcpy(char* dest, const char* src)
{
	size_t i = 0;

	while (*(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	
	*(dest + i) = '\0';
	
	return dest;
} 

char* Strncpy(char* dest, const char* src, size_t n)
{
	size_t i = 0;
	
	while (*(src+i) != '\0' && i < n)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	
	while (i < n)
	{
		*(dest + i) = '\0';
		i++;
	}

	return dest;
}



/* for the use of Strcasecmp*/

char UpperToLower(char letter)
{
	if (64 < letter && 91 > letter)
	{		
		letter += 32;
	}
	
	return letter;
}


int Strcasecmp(const char* str1, const char* str2)
{
	while (UpperToLower(*str1) == UpperToLower(*str2) && (*str1 || *str2))
	{
		str1++;
		str2++;
	}
	
	return (*str1 - *str2);
}

char* Strchr (const char* str, int c)
{
	while (*str != c && *str != '\0')
	{
		str++;
	}
	
	if (*str != c)
	{
		return NULL;
	}
	
	return (char*)str;
}


char* Strdup(const char* str)
{
	size_t i = 0, len = Strlen(str);
	char* dup;
	dup = malloc(len);

	if (dup == NULL)
	{
		printf("ERRORRRRRR");
		return NULL;
	}
	
	for(i = 0; i < len; i++)
	{
		*(dup + i) = *(str + i);
	}

	return dup;
}


char* Strcat(char* dest, const char* source)
{
	char* buffer = dest + Strlen(dest);

	Strcpy(buffer, source);
	
	return dest;

}

char* Strncat(char* dest, const char* source, size_t n)
{
	char* buffer = dest + Strlen(dest);

	Strncpy(buffer, source, n);
	
	return dest;

}

int Strncmp(const char* str1, const char* str2, int n)
{

	while (*str1 == *str2 && (*str1 || *str2) && 0 < (n - 1))
	{
		str1++;
		str2++;
		n--;
	}
	
	return (*str1 - *str2);

}

char* Strstr(const char* haystack, const char* needle)
{	

	while((haystack = Strchr(haystack, *needle)))
	{
		if (!Strncmp(haystack, needle, Strlen(needle)))
		{
			return (char*)haystack;
		}
		
		haystack++;
	}
	return (char*)haystack;
}

size_t Strspn(const char* s, const char* accept)
{
	const char* buffer = s;
	while((Strchr(accept, *buffer)))
	{
		buffer++;
	}
	return (buffer - s);
}

char* Strtok(char* str, const char* delim)
{
	static char* static_str;
	char* buffer;

	if(str)
	{
		 static_str = Strdup(str);
	}
	while(Strchr(delim, *static_str) && *static_str != '\0')
	{
		static_str++;
	}
	
	buffer = static_str;

	while(!Strchr(delim, *static_str) && *static_str != '\0')
	{
		static_str++;
	}
	
	if(*static_str)
	{
		*static_str = '\0';
		static_str++;
		return buffer;
	}

	return buffer;
}

int IsPalindrome(const char* str)
{
	size_t len = Strlen(str);
	int iterations = len / 2;
	const char* str2 = str + len - 1;

	while(*str == *str2 && iterations)
	{
		str++;
		str2--;
		iterations--;
	} 
	
	return (*str == *str2);
}

/* implementation of SevenBoom using strings */

/*

int NumOfDig(int num)
{
	int counter = 0;
	while(num != 0)
	{
		counter += 1;
		num /= 10;
	}

	return counter;
	
}

void SevenBoomStr(int from, int to)
{
	char* str;
	int len, current;

	for (from; from < to; from++)
	{	
		
		current = from;
		len = NumOfDig(current);
		str = malloc(len + 1);
		*(str + len) = '\0';
		len--;
		
		while(len >= 0)
		{
			
			*(str + len) = (current % 10) + 48;
			current /= 10;
			len--;
		}
		
		if(Strchr(str, '7')
		{
			printf("BOOM, ");
		}
		else
		{
			printf("%s, ", str);
		}
		
		free(str);
	}
}

*/

int ContainsDigit(int num, int digit)
{
	while(num != 0)
	{
		if(num % 10 == digit)
		{
			return 1;
		}
		num /= 10;
	}
	
	return 0;
}

void SevenBoom(int from, int to)
{
	for(from; from < to; from++)
	{
		if(!(from % 7) || ContainsDigit(from, 7))
		{
			printf("BOOM ");
		}
		else
		{
			printf("%d ", from);
		}
	}	
}

void SwapPtrs(int** a, int** b)
{
	int* temp = *a;
	*a = *b;
	*b = temp;
}

void RmSpaces (char* str)
{
	char* delimiters = "	 ";
	char* buffer = str;
	char* word = Strtok(str, delimiters);

	if(*word == '\0') /* if str contains only white spaces and tabs, shrink it to a single white space */
	{
		*(str + 1) = '\0';
		return;
	}
	
	while(*word != '\0')
	{
		Strcpy(buffer, word);
		buffer += Strlen(word);
		*buffer = ' ';
		buffer += 1;
		word = Strtok(NULL, delimiters);
	}
	
	*(buffer - 1) = '\0';
}


char* SumBigNums(char* str1, char* str2)
{

	int sum_dig = 0, quotient = 0,len_big = 0, len_small = 0, len_diff = 0;
	char* sum = NULL;
	char* big = NULL;
	char* small = NULL;

	if(Strlen(str1) > Strlen(str2))
	{
		len_big = Strlen(str1);
		len_small = Strlen(str2);
		big = str1 + (len_big - 1);
		small = str2 + (len_small - 1);
	}

	else
	{
		len_big = Strlen(str2);
		len_small = Strlen(str1);
		big = str2 + (len_big - 1);
		small = str1 + (len_small - 1);
	}
	
	len_diff = len_big - len_small;
	sum = malloc(len_big + 2);
	sum += len_big + 1;
	*sum = '\0';
	sum--;
	
	for(; len_small; len_small--)
	{
		sum_dig = ((*big - '0') + (*small - '0') + quotient);
		*sum = ((sum_dig % 10) + '0');
		quotient = (sum_dig / 10);
		sum--;
		big--;
		small--;
	}

	for(; len_diff; len_diff--)
	{
		sum_dig = ((*big - '0') + quotient);
		*sum = ((sum_dig % 10) + '0');
		quotient = (sum_dig / 10);
		sum--;
		big--;
	}
	
	if(quotient)
	{
		*sum = quotient + '0';
	}
	
	else
	{
		sum++;
	}

	return sum;
}











































