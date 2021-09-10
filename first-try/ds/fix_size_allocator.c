#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdio.h> /* printf */

#include "fix_size_allocator.h"

#define WORD sizeof(size_t)

struct allocator
{
    size_t block_size;
    size_t nblocks;
    size_t nblocks_free;
    void** next_free;
};

void Print(allocator_t* allocator)
{
    void** iter = allocator->next_free;
    size_t i = 0;

    for (i = 0; i < allocator->nblocks_free; i++, iter = *iter)
    {
        printf("current %lu\nnext %lu\n",(size_t)iter, (size_t)*iter);
    }
}


static size_t WordAlign(size_t num)
{
    return ((WORD - (num % WORD)) % WORD) + num;
}

/*****************************************************************/

size_t FSASuggestSize(size_t block_size, size_t num_of_blocks)
{
    size_t total_size = 0;

    if (block_size == 0 || num_of_blocks == 0)
    {
        return 0;
    }

    total_size = WordAlign(sizeof(allocator_t)) + 
                        WordAlign(block_size + WORD) * num_of_blocks + 
                        WORD - 1;

    return total_size;
}

allocator_t* FSAInit(void* dest, size_t block_size, size_t total_size)
{
    size_t i = 0;
    size_t actual_block_size = WordAlign(block_size + WORD);
    allocator_t* allocator = (allocator_t*)WordAlign((size_t)dest);
    size_t start_adress = (size_t)(allocator + 1);
    size_t end_adress = (size_t)dest + total_size;

    if (block_size == 0 || total_size == 0 ||
        end_adress < start_adress + actual_block_size)
    {
        return NULL;
    }

    allocator->block_size = block_size;
    allocator->nblocks = (end_adress - start_adress) / actual_block_size;
    allocator->nblocks_free = allocator->nblocks;
    allocator->next_free = (void**)start_adress;

    for (i = 0; i < allocator->nblocks; ++i)
    {
        *((void**)start_adress) = (void*)(start_adress + actual_block_size);        
        start_adress += actual_block_size;
    }

    *((void**)(start_adress - actual_block_size)) = NULL;

    return allocator;
}

size_t FSAGetBlockSize(const allocator_t *allocator)
{
    assert(allocator);
    return allocator->block_size;
}

size_t FSACountFree(const allocator_t *allocator)
{
    assert(allocator);
    return allocator->nblocks_free;
}

void* FSAAlloc(allocator_t *allocator)
{
    size_t swapper = 0;

    if (allocator->nblocks_free == 0)
    {
        return NULL;
    }

    swapper = (size_t)allocator->next_free;
    allocator->next_free = *(allocator->next_free);
    allocator->nblocks_free--;
    *((void**)swapper) = allocator;
    swapper += WORD;

    return (void*)swapper;
}

void FSAFree(void *block)
{
    void** meta_block = ((void**)block - 1);
    allocator_t* allocator = (allocator_t*)(*meta_block);
    *meta_block = allocator->next_free;
    allocator->next_free = meta_block;
    allocator->nblocks_free++;
}