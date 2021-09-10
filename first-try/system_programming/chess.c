#include <stdio.h>

typedef struct
{
    int row;
    int col;

} point_t;

void PrintTable();
void Chess(int row, int col);
int RecFunc(point_t* point);
int NotValid(point_t* point);
int PointToInt(point_t* point);
int IsUsed(point_t* point);
void SetUsed(point_t* point);
void UnsetUsed(point_t* point);
int Success();
void SetNextPossibilities(point_t* point, point_t* next);
void SetByOptions(point_t* next);
int GetValidOptions(point_t* point);
void InsertionSort(point_t* next, int* options, int size);
void Swap(int* options, point_t* next, int idx1, int idx2);
int FindMinIdx(int* options, int size);

int TABLE[64];

size_t bitsarr;

int main()
{
    int i = 0;
    int j = 0;

    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; j++)
        {
            Chess(i, j);
            bitsarr = 0;
        }
    }

    return 0;
}

void PrintTable()
{
    int i = 0;
    int j = 0;

    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 8; ++j)
        {
            printf("%2d ", TABLE[i * 8 + j]);
        }
        puts("");
    }
}

void Chess(int row, int col)
{
    point_t point = {0};
    
    point.row = row;
    point.col = col;

    RecFunc(&point);

    PrintTable();
    puts(""); 
}

int RecFunc(point_t* point)
{
    int status = -1;
    int i = 0;
    point_t next[8];

    if (NotValid(point) || IsUsed(point))
    {
        return -1;
    }

    SetUsed(point);

    if (Success())
    {
        TABLE[PointToInt(point)] = 63;

        return 62;
    }

    SetNextPossibilities(point, next);
    SetByOptions(next);

    for (i = 0; i < 8; ++i)
    {
        status = RecFunc(&next[i]);

        if (status != -1)
        {
            TABLE[PointToInt(point)] = status;

            return status - 1;
        }
    }

    UnsetUsed(point);
    
    return -1;
}

void SetByOptions(point_t* next)
{
    int options[8];
    int i = 0;

    for (i = 0; i < 8; ++i)
    {
        options[i] = GetValidOptions(&next[i]);
    }

    InsertionSort(next, options, 8);
}

int GetValidOptions(point_t* point)
{   
    int i = 0;
    int num_options = 0;
    point_t options[8];
    SetNextPossibilities(point, options);

    for (i = 0; i < 8; ++i)
    {
        if (NotValid(&options[i]) || IsUsed(&options[i]))
        {
            continue;
        }

        num_options++;
    }

    return num_options;
}

void InsertionSort(point_t* next, int* options, int size)
{
    int min_idx = 0;

    if (size == 1)
    {
        return;
    }

    min_idx = FindMinIdx(options, size);

    Swap(options, next, 0, min_idx);

    InsertionSort(next + 1, options + 1, size - 1);
}

void Swap(int* options, point_t* next, int idx1, int idx2)
{
    int int_tmp = options[idx1];
    point_t point_tmp = next[idx1];

    options[idx1] = options[idx2];
    next[idx1] = next[idx2];

    options[idx2] = int_tmp;
    next[idx2] = point_tmp;
}

int FindMinIdx(int* options, int size)
{
    int i = 0;
    int min_idx = 0;

    for (i = 1; i < size; ++i)
    {
        if (options[i] < options[min_idx])
        {
            min_idx = i;
        }
    }

    return min_idx;
}

int NotValid(point_t* point)
{
    return point->row < 0 || point->col < 0 || point->row > 7 || point->col > 7;
}

int PointToInt(point_t* point)
{
    return point->row * 8 + point->col;
}

int IsUsed(point_t* point)
{
    return (bitsarr & 1UL << PointToInt(point)) != 0;
}

void SetUsed(point_t* point)
{
    bitsarr |= 1UL << PointToInt(point);
}

void UnsetUsed(point_t* point)
{
    bitsarr &= ~(1UL << PointToInt(point));
}

int Success()
{
    return bitsarr == ~0UL;
}

void SetNextPossibilities(point_t* point, point_t* next)
{
    next[0].row = point->row + 1;
    next[0].col = point->col + 2;
    next[1].row = point->row + 1;
    next[1].col = point->col - 2;
    next[2].row = point->row - 1;
    next[2].col = point->col + 2;
    next[3].row = point->row - 1;
    next[3].col = point->col - 2;
    next[4].row = point->row + 2;
    next[4].col = point->col + 1;
    next[5].row = point->row + 2;
    next[5].col = point->col - 1;
    next[6].row = point->row - 2;
    next[6].col = point->col + 1;
    next[7].row = point->row - 2;
    next[7].col = point->col - 1;
}
