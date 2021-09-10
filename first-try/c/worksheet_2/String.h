#ifndef __STRING_H__
#define __STRING_H__
#include <stddef.h> /* size_t */


/* calculate the length of a string */
size_t Strlen(const char* str);

/* compare two strings */
int Strcmp(const char* str1, const char* str2);

/* copies a string */
char* Strcpy (char* dest, const char* src);


char* Strncpy (char* dest, const char* src, size_t n);

/* to help with Strcasecmp */
char UpperToLower(char letter);

/* compare two strings ignoring letter case */
int Strcasecmp(const char* str1, const char* str2);

/* locate character in string */
char* Strchr (const char* str, int c);

/* duplicate a string using dynamic memory allocation */
char* Strdup(const char* str);

/* concatenate two strings */
char* Strcat(char* dest, const char* source);


char* Strncat(char* dest, const char* source, size_t n);

/* to help with Strstr */
int Strncmp(const char* str1, const char* str2, int n);

/* locate a substring */
char* Strstr(const char* haystack, const char* needle);

/* get length of a prefix substring */
size_t Strspn(const char* s, const char* accept);

/* extract tokens from strings */
char* Strtok(char* str, const char* delim);

int IsPalindrome(const char* str);

/*
int NumOfDig(int num);

void SevenBoomStr(int from, int to)
*/

int ContainsDigit(int num, int digit);

void SevenBoom(int from, int to);

void SwapPtrs(int** a, int** b);

void RmSpaces (char* str);

char* SumBigNums(char* str1, char* str2);

#endif
