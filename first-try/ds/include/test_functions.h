#ifndef TEST_FUNCTIONS
#define TEST_FUNCTIONS

#include <stddef.h> /* size_t */

void VerifySizeT(size_t result, size_t expected, char* name);

void VerifySizeTNot(size_t result, size_t expected, char* name);

void VerifyInt(int result, int expected, char* name);

void VerifyIntNot(int result, int expected, char* name);

void VerifyString(char* result, char* expected, char* name);

void VerifyPointer(void* result, void* expected, char* name);

void VerifyPointerNot(void* result, void* expected, char* name);

#endif
