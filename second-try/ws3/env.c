#include <stdio.h> //printf
#include <malloc.h> //malloc, free
#include <stddef.h> //size_t
#include <string.h> //strlen
#include <ctype.h> //tolower



void _CopyStrToLower(char *dest, char *src) {
    size_t i = 0;
    for (i = 0; i < strlen(src); ++i)
    {   
        dest[i] = tolower(src[i]);        
    }
    dest[i] = '\0';
}

size_t EnvLen(char **env) {
    size_t len = 0;
    while (*env != NULL)
    {   ++len;
        ++env;
    }

    return len;
}

void PrintArrays(char** src, char **copy, size_t len) {
    printf("\n\n");
    for (size_t i = 0; i < len; ++i)
    {
        printf("%s\n%s\n\n", src[i], copy[i]);
    }
    printf("\n\n");
}

void DestroyEnvArr(char **arr, size_t len) {
    for (size_t i = 0; i < len; ++i)
    {
        free(arr[i]);
    }
    free(arr);
    arr = NULL;
}

//create a copy of envp including the void ptr at the end. all strings in lower case.
char ** CreateEnvArrInLower(char **src, size_t len) { 

    char ** dest = malloc((len + 1) * sizeof(char**));
    if (dest == NULL) {
        return NULL;
    }

    size_t i = 0;
    for (i = 0; i < len; ++i)
    {
        dest[i] = malloc(strlen(src[i]) + 1);
        if (dest[i] == NULL)
        {
            DestroyEnvArr(dest, i);
            return NULL;
        }
        _CopyStrToLower(dest[i], src[i]);
    }
    dest[i] = NULL;

    return dest;
} 

int main(int argc, char** argv, char** envp) {
    size_t envp_len = EnvLen(envp);
    char **copy = CreateEnvArrInLower(envp, envp_len);
    if (copy == NULL) {
        return -1;
    }
    PrintArrays(envp, copy, envp_len);
    DestroyEnvArr(copy, envp_len);
    return 0;
}