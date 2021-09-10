#include <ctype.h> /* tolower */
#include <stddef.h>/* size_t */


int sourceLen(const char** source)
{
	size_t i = 0;

	while (*(source + i))
	{
		i++;
	}
	
	return i;

}

char* StrCpyToLower(char* dest, const char* source)
{
	while (*source)
	{
		*dest = tolower(*source);
		++dest;
		++source;
	}
	
	*dest = '\0';
	return dest;
}


size_t StrToSizet(const char* str)
{
	size_t result = 0;

	while (*str)
	{
		result *= 10;
		result += (*str - '0');
		++str; 	
	}
	
	return result;
}











