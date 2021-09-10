#include <stddef.h> /* size_t ptrdiff_t */
#include <stdio.h>

#include "var_size_allocator.h"

#define WORD sizeof(size_t)
#define BLOCK sizeof(block_t)
#define VSA sizeof(vsa_t)

enum Fitness {FIT, NOT_FIT};

typedef struct block
{
    ptrdiff_t next_block;
#ifndef NDEBUG
    size_t magic_num;
#endif
}block_t;

struct var_alloc
{
    size_t total_size;
};

/***************************** SIDE FUNCTIONS **********************************/

static size_t AlignUp(size_t num)
{
    return ((WORD - (num % WORD)) % WORD) + num;
}

static size_t AlignDown(size_t num)
{
    return (num - (num % WORD));
}

static void* SetNewBlock(block_t* cur_block, size_t block_size)
{
    block_t* new_block = (block_t*)((size_t)(cur_block + 1) + block_size);
    new_block->next_block = cur_block->next_block - BLOCK - block_size;

#ifndef NDEBUG
    cur_block->magic_num = 0xDEADBEAF;
#endif

    cur_block->next_block = (BLOCK + block_size) * -1;

    return (void*)(cur_block + 1);
}

static size_t Abs(ptrdiff_t num)
{
    if (num < 0)
    {
        num *= -1;
    }

    return (size_t)num;
}

static int IsEnoughMemory(block_t* cur_block, size_t block_size, size_t end_adress)
{
    return (size_t)cur_block + BLOCK + block_size <= end_adress;
}

static int IsEnoughMemoryForTwo(block_t* cur_block, size_t block_size)
{
    return BLOCK * 2 + block_size + WORD <= Abs(cur_block->next_block);
}

static int IsTaken(block_t* cur_block)
{
    return cur_block->next_block < 0;
}

static block_t* NextBlock(block_t* cur_block)
{
    return (block_t*)((size_t)cur_block + Abs(cur_block->next_block));
}

static enum Fitness BlockFitness(block_t* cur_block, size_t block_size)
{
    if (cur_block->next_block - BLOCK < block_size)
    {
        return NOT_FIT;
    }

    return FIT;
}

static void* Allocate(block_t* cur_block)
{
    cur_block->next_block *= -1;

#ifndef NDEBUG
        cur_block->magic_num = 0xDEADBEAF;
#endif

    return (void*)(cur_block + 1);
}

static size_t Max(size_t num1, size_t num2)
{
    return (num1 > num2 ? num1 : num2);
}

static void Merge(block_t* cur_block, block_t* next_block)
{
    cur_block->next_block += next_block->next_block;
}

/******************************** API FUNCTIONS *************************************/

vsa_t* VSAInit(void* seg, size_t total_size)
{
    vsa_t* vsa = NULL;
    block_t* first_block = NULL;
    size_t start_address = AlignUp((size_t)seg);
    size_t end_address = AlignDown((size_t)seg + total_size);

    if (end_address < start_address + VSA + BLOCK + WORD)
    {
        return NULL;
    }

    vsa = (vsa_t*)start_address;
    first_block = (block_t*)(start_address + VSA);
    vsa->total_size = end_address - start_address - VSA;
    first_block->next_block = vsa->total_size;

    return vsa;
}

void* VSAAlloc(vsa_t* vsa, size_t block_size)
{
    block_t* cur_block = (block_t*)(vsa + 1);
    block_t* next_block = NULL;
    size_t end_address = (size_t)(vsa + 1) + vsa->total_size;
    block_size = AlignUp(block_size);

    while (IsEnoughMemory(cur_block, block_size, end_address))
    {
        if (IsTaken(cur_block))
        {
            cur_block = NextBlock(cur_block);
            continue;
        }

        switch (BlockFitness(cur_block, block_size))
        {
            case FIT:
            {
                if (IsEnoughMemoryForTwo(cur_block, block_size))
                {
                    return SetNewBlock(cur_block, block_size);
                }

                return Allocate(cur_block); 
            }
            
            case NOT_FIT:
            {
                next_block = NextBlock(cur_block);

                if (IsTaken(next_block))
                {
                    cur_block = next_block;
                }

                else
                {
                    Merge(cur_block, next_block);
                }
            } 
        }
    }    

    return NULL;
}

void VSAFree(void *block)
{
    block_t* cur_block = NULL;

    if (!block)
    {
        return;
    }

    cur_block = ((block_t*)block) - 1;

#ifndef NDEBUG
    if (cur_block->magic_num != 0xDEADBEAF)
    {
        return;
    }
    cur_block->magic_num = 0;
#endif

    cur_block->next_block *= -1;
}

size_t VSAGetLargestBlock(const vsa_t* vsa)
{
    size_t largest = 0;
    size_t current_block_size = 0;
    size_t end_address = (size_t)(vsa + 1) + vsa->total_size;
    block_t* cur_block = (block_t*)(vsa + 1);
    block_t* next_block = NULL;

    while ((size_t)cur_block < end_address)
    {
        if (IsTaken(cur_block))
        {
            cur_block = NextBlock(cur_block);
            continue;
        }

        next_block = NextBlock(cur_block);
    
        if ((size_t)next_block == end_address || IsTaken(next_block))
        {
            current_block_size = cur_block->next_block - BLOCK;

            largest = Max(largest, current_block_size);

            cur_block = next_block;
            continue;
        }
        
        Merge(cur_block, next_block);        
    }

    return largest;
}

