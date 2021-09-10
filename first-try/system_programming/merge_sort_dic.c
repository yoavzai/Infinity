/* Benchmark for 1000 copies of dic:

1: 30.285s
2: 19.930s
3: 20.444s
4: 20.063s
5: 19.925s
6: 20.160s
10: 20.335s
50: 20.601s
1000: 21.699s

*/



#include <stdlib.h> /* malloc, free */
#include <stdio.h>
#include <string.h> /* strcmp */
#include <time.h> /* time */
#include <pthread.h>

#define N_THREADS 5000
#define N_COPIES 1000

typedef struct
{
    char** src;
    size_t size;

}data_t;

void InitDic();
void PrintDic(char** dic);
void Swap(char** ptr1, char** ptr2);
void ShuffleDic(char** dic);
void* MergeSortThread(void* data);
void Merge(char** buffer, data_t* left_data, data_t* right_data);
int CmpDics(char** dic1, char** dic2);

char* words;
char** words_ptrs;
size_t n_words;

int main()
{
    pthread_t thread = 0;
    data_t data_for_thread = {0};
    char** shuffled;

    InitDic();

    shuffled = (char**)malloc(n_words * sizeof(char*));
    memcpy(shuffled, words_ptrs, n_words * sizeof(char*));

    ShuffleDic(shuffled);

    data_for_thread.src = shuffled;
    data_for_thread.size = n_words;

    pthread_create(&thread, NULL, MergeSortThread, &data_for_thread);
    pthread_join(thread, NULL);

    free(words);
    free(words_ptrs);
    free(shuffled);

    return 0;
}

int CmpDics(char** dic1, char** dic2)
{
    size_t i = 0;

    for (i = 0; i < n_words; ++i)
    {
        if (dic1[i] != dic2[i])
        {
            return -1;
        }
    }

    return 0;
}

void InitDic()
{
    size_t i = 0;
    size_t bytes = 0;
    char** cur_ptr = NULL;
    char* cur_char  = NULL;
    FILE* tmp = fopen("/tmp/words", "w+");
    FILE* dic = fopen("/usr/share/dict/words", "r");
    system("wc -cl /usr/share/dict/words > /tmp/words");
    fscanf(tmp,"%lu" "%lu", &n_words, &bytes);
    fclose(tmp);

    words = (char*)malloc(bytes);
    words_ptrs = (char**)malloc(N_COPIES * n_words * sizeof(char*));
    cur_ptr = words_ptrs;
    cur_char = words;

    *cur_ptr = cur_char;
    cur_ptr++;

    while ((*cur_char = getc(dic)) != EOF)
    {
        if (*cur_char == '\n')
        {
            *cur_char = '\0';
            cur_char++;
            *cur_ptr = cur_char;
            cur_ptr++;
            
            continue;
        }

        cur_char++;
    }

    for (i = 1; i < N_COPIES; ++i)
    {
        memcpy(words_ptrs + (i * n_words), words_ptrs, n_words * sizeof(char*));
    }

    n_words *= N_COPIES;

    fclose(dic);
}

void* MergeSortThread(void* data)
{   
    size_t size = ((data_t*)data)->size;
    char** src = ((data_t*)data)->src;
    char** buffer = NULL;
    data_t left_data = {0};
    data_t right_data = {0};

    left_data.src = src;
    left_data.size = size / 2;
    right_data.src = src + left_data.size;
    right_data.size = size - left_data.size;

    if (size == 1)
    {
        free(buffer);
        return NULL;
    }

    else if (size < n_words / N_THREADS)
    {
        MergeSortThread(&left_data);
        MergeSortThread(&right_data);
    }

    else
    {
        pthread_t left_thread = 0;
        pthread_t right_thread = 0;

        pthread_create(&left_thread, NULL, MergeSortThread, &left_data);
        pthread_create(&right_thread, NULL, MergeSortThread, &right_data);
        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);
    }
    
    buffer = (char**)malloc(size * sizeof(char**));
    Merge(buffer, &left_data, &right_data);
    memcpy(src, buffer, size * sizeof(char*));

    free(buffer);

    return NULL;
}

void Merge(char** buffer, data_t* left_data, data_t* right_data)
{
    size_t lidx = 0;
    size_t ridx = 0;

    while (lidx < left_data->size && ridx < right_data->size)
    {
        if (strcmp((left_data->src)[lidx], (right_data->src)[ridx]) <= 0)
        {
            buffer[lidx + ridx] = (left_data->src)[lidx];
            lidx++;
        }

        else
        {
            buffer[lidx + ridx] = (right_data->src)[ridx];
            ridx++;
        }
    }

    while (lidx < left_data->size)
    {
        buffer[lidx + ridx] = (left_data->src)[lidx];
        lidx++;
    }

    while (ridx < right_data->size)
    {
        buffer[lidx + ridx] = (right_data->src)[ridx];
        ridx++;
    }
}

void PrintDic(char** dic)
{
    size_t i = 0;

    for (i = 0; i < n_words; ++i)
    {
        printf("%s\n", dic[i]);
    }
}

void Swap(char** ptr1, char** ptr2)
{
    char* tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
}

void ShuffleDic(char** dic)
{
    size_t idx = 0;
    size_t idx2 = 0;

    srand(time(NULL));

    for (idx = n_words - 1; idx > 0; --idx)
    {
        idx2 = rand() % (idx + 1);

        Swap(dic + idx, dic + idx2);
    }
}
