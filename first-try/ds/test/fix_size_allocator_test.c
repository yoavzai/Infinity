#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define RESET "\x1b[0m"
#define REQUIRE(cond) ((cond) ? printf(GREEN"SUCCESS\n") : printf(RED"FAIL\n"))

#include "fix_size_allocator.h"

int main()
{
    size_t i = 0;
    void* allocs[5];
    size_t total_size = FSASuggestSize(13, 5);
    char* a = malloc(total_size);
    allocator_t* allocator = FSAInit(a+1, 13, total_size);

    REQUIRE(a + 8 == (void*)allocator);
    REQUIRE(FSACountFree(allocator) == 5);
    REQUIRE(FSAGetBlockSize(allocator) == 13);
    
    allocs[0] = FSAAlloc(allocator);
    strcpy(allocs[0], "1st  allocation");
    allocs[1] = FSAAlloc(allocator);
    strcpy(allocs[1], "2nd  allocation");
    allocs[2] = FSAAlloc(allocator);
    strcpy(allocs[2], "3rd  allocation");
    allocs[3] = FSAAlloc(allocator);
    strcpy(allocs[3], "4th  allocation");
    allocs[4] = FSAAlloc(allocator);
    strcpy(allocs[4], "5th  allocation");

    for (i = 0; i < 5; i++)
    {
        printf(RESET"%s\n", (char*)allocs[i]);
    }
    
    REQUIRE(FSACountFree(allocator) == 0);

    for (i = 0; i < 5; i++)
    {
        FSAFree(allocs[i]);
    }

    for (i = 0; i < 5; i++)
    {
        allocs[i] = FSAAlloc(allocator);
    }
    
    for (i = 0; i < 5; i++)
    {
        printf(RESET"%s\n", (char*)allocs[i]);
    }

    REQUIRE(FSAInit(a, 13, 20) == NULL);
    REQUIRE(FSASuggestSize(13, 0) == 0);
    REQUIRE(FSASuggestSize(0, 22) == 0);

    return 0;
}

/*
SUCCESS
SUCCESS
SUCCESS
1st  allocation
2nd  allocation
3rd  allocation
4th  allocation
5th  allocation
SUCCESS
5th  allocation
4th  allocation
3rd  allocation
2nd  allocation
1st  allocation
SUCCESS
SUCCESS
SUCCESS
*/