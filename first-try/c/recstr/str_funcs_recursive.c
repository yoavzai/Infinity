#include <stddef.h> /* size_t */
#include <stdio.h> /* printf */

size_t Strlen(const char *s)
{
    assert(s);

    if ('\0' == *s)
    {
        return 0;
    }

    return 1 + Strlen(s + 1);
}

int Strcmp(const char *s1, const char *s2)
{
    assert(s1);
    assert(s2);

    if (*s1 != *s2 || '\0' == *s1)
    {
        return *s1 - *s2;
    }

    return Strcmp(s1 + 1, s2 + 1);
}

char *Strcpy(char *dest, const char *src)
{
    assert(dest);
    assert(src);

    *dest = *src;

    if ('\0' == *src)
    {
        return dest;
    }

    return Strcpy(dest + 1, src + 1) - 1;
}

char *Strcat(char *dest, const char *src)
{
    assert(dest);
    assert(src);

    return Strcpy(dest + Strlen(dest), src);
}

char *Strstr(const char *haystack, const char *needle)
{
    assert(haystack);
    assert(needle);

    if (Strlen(haystack) < Strlen(needle))
    {
        return NULL;
    }

    if (!Strncmp(haystack, needle, Strlen(needle)))
    {
        return (char*)haystack;
    }

    return Strstr(haystack + 1, needle);
}

static int Strncmp(const char *s1, const char *s2, size_t n)
{
    assert(s1);
    assert(s2);

    if (0 == n)
    {
        return 0;
    }

    if (*s1 != *s2)
    {
        return *s1 - *s2;
    }

    return Strncmp(s1 + 1, s2 + 1, n - 1);
}

int main()
{
    char* str = "3456";
    char str2[9];
    char* result = Strstr(str, str2);
    *str2 = '1';
    *(str2 + 1) = '2'; 
    *(str2 + 2) = '\0'; 

    printf("%s\n", str2);
    Strcat(str2, str);
    printf("%s\n", str2);


    /*
    if (result == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("%s\n", result);
    }
    */

    return 0;
}