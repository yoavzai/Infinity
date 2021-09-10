#ifndef FUNCS
#define FUNCS

#include <stdio.h>
#include <stddef.h>

size_t CreateWordForMemset(char byte);
int Min(size_t x, size_t y);
size_t CreateWordForMemcpy(size_t* src_p, int offset);
char* ReverseString(char* str);
int CharToInt(char ch);

#endif


