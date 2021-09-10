#ifndef EXERCISE
#define EXERCISE

#include <stdio.h>
#include <stddef.h>

void* Memset(void* dest_p, int data, size_t num_bytes);
void* Memcpy(void* dest_p, const void* src_p, size_t num_bytes);
void* Memmove(void* dest_p, const void* src_p, size_t num_bytes);
char* Itoa(int num, char* buffer);
int Atoi(char* str, int base); 
void PrintUnique(char* str1, char* str2, char* str3);
void WhichEndian();

#endif
