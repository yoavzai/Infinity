#include <stdio.h> //printf


int IsSpace(const char c) {
    return (c == ' ' || c == '\t');
}


char * FirstNonSpace(char* ptr) {
    while (IsSpace(*ptr))
    {
        ++ptr;
    }
    return ptr;
}

void ClearEndSpaces(char *str) {
    while (*str != '\0')
        ++str;
    --str;
    while (IsSpace(*str))
        --str;
    ++str;
    *str = '\0';
}


void ClearSpaces(char *str) {
    ClearEndSpaces(str);
    char *runner = FirstNonSpace(str);
    while (*runner != '\0')
    {
        if (IsSpace(*runner) && IsSpace(*(runner-1)))
            {
                ++runner;
                continue;
            }
        *str = *runner;
        ++runner;
        ++str;
    }
    *str = '\0';
}


int main() {
    char str1[] = "     Hi,    I'm string   no'  1   ";
    char str2[] = "Hi, I'm string no' 2";
    char str3[] = "      Hi,   I'm string   no'  3";
    char str4[] = "Hi,    I'm string   no'  4   ";

    char * strings[] = {str1, str2, str3, str4};

    for (int i=0; i < sizeof(strings); ++i)
    {
        printf("Before: |%s|\n", strings[i]);
        ClearSpaces(strings[i]);
        printf("After: |%s|\n", strings[i]);
    }

    return 0;
}