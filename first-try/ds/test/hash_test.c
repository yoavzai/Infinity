#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <string.h> /* strlen, strcmp */

#include "hash.h"

#define RED "\033[22;31m"
#define GREEN "\033[22;32m"
#define RESET "\x1B[0m"
#define REQUIRE(x,y) (x == y ? printf(GREEN"SUCCESS\n"RESET) : printf(RED"FAIL\n"RESET))

int PrintHash(void* data, void* param)
{
    (void)param;

    printf("%s\n", (char*)data);

    return 0;
}

size_t HashFunc(const void *data)
{
    char* word = '\0';

    assert(data);

    word = (char*)data;

    assert(strlen(word));

    return *word - 'a';
}

int CompFunc(const void *data1, const void *data2)
{
    return strcmp((char*)data1, (char*)data2);
}

int main()
{
    size_t i = 0;
    char* dic[] = {"a", "abba", "body", "buy", "dad", "deliver", "europe"};

    hash_t *hash = HTCreate(HashFunc, 5, CompFunc, NULL);

    printf("Size "); REQUIRE(HTSize(hash), 0);
    printf("IsEmpty "); REQUIRE(HTIsEmpty(hash), 1);


    for (i = 0; i < sizeof(dic)/sizeof(dic[0]); ++i)
    {
        HTInsert(hash, dic[i]);
    } 

    printf("Find "); REQUIRE(HTFind(hash, "buy"), dic[3]);
    printf("Find "); REQUIRE(HTFind(hash, "buyy"), NULL);
    printf("Size "); REQUIRE(HTSize(hash), 7);
    printf("IsEmpty "); REQUIRE(HTIsEmpty(hash), 0);
    puts("");

    HTForEach(hash, PrintHash, NULL);
    puts("");
    HTRemove(hash, "dad");
    HTRemove(hash, "dadd");
    printf("Remove "); REQUIRE(HTSize(hash), 6);
    HTForEach(hash, PrintHash, NULL);
    puts("");

    HTDestroy(hash);

    return 0;
}