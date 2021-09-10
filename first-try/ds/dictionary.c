#include <stdlib.h>
#include <stdio.h>
#include <string.h> /* strcmp */
#include <ctype.h> /* tolower */

#include "hash.h"

int cmp_func(const void *data1, const void *data2)
{
    return strcmp((char*)data1, (char*)data2);
}

size_t hash_func(const void *data)
{
    return (tolower(*((char*)data)) - 'a') % 26;
}

char* InitDic(hash_t* hash)
{
    size_t bytes = 0;
    char *bigstr = NULL;
    char *word = NULL;
    char *cur_char  = NULL;
    FILE* tmp = fopen("/tmp/words", "w+");
    FILE *dic = fopen("/usr/share/dict/words", "r");
    system("wc -c /usr/share/dict/words > /tmp/words");
    fscanf(tmp,"%lu", &bytes);
    fclose(tmp);
    
    bigstr = (char*)malloc(bytes);
    word = bigstr;
    cur_char  = word;

    while ((*cur_char = getc(dic)) != EOF)
    {
        if (*cur_char == '\n')
        {
            *cur_char = '\0';
            HTInsert(hash, word);
            cur_char++;
            word = cur_char;
            continue;
        }

        cur_char++;
    }

    fclose(dic);

    return bigstr;
}

int main(int argc, char* argv[])
{
    hash_t *hash = HTCreate(hash_func, 26, cmp_func, NULL);
    char *bigstr = 0;

    if (argc < 2)
    {
        HTDestroy(hash);

        return 1;
    }

    bigstr = InitDic(hash);

    printf("%d\n", (HTFind(hash, argv[1]) != NULL));

    HTDestroy(hash);
    free(bigstr);

    return 0;
}