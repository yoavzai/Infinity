#include <stdio.h>
#include <stdlib.h>

#include "var_size_allocator.h"

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define RESET "\x1b[0m"
#define REQUIRE(cond) ((cond) ? printf(GREEN"SUCCESS\n") : printf(RED"FAIL\n"))


int main()
{
    char* a = (char*)malloc(38);

#ifndef NDEBUG
    REQUIRE(VSAInit(a + 1, 38) == NULL);
    REQUIRE(VSAInit(a + 2, 38) != NULL);
#endif

    REQUIRE(VSAInit(a + 1, 30) == NULL);
    
    return 0;
}