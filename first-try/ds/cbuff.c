#include <stdlib.h> /* malloc, free */
#include <sys/types.h> /* ssize_t */
#include <string.h> /* memcpy */

#include "cbuff.h"

#define MIN(a,b) ((a) < (b) ? (a) : (b))


struct c_buff
{
    char* data;
    size_t capacity;
    size_t size;
    size_t read_idx;    
};

cbuff_t* CBuffCreate(size_t capacity)
{
    cbuff_t* new_cbuff;

    if (capacity == 0)
    {
        return NULL;
    }

    new_cbuff = malloc(sizeof(cbuff_t) + capacity);

    if (new_cbuff == NULL)
    {
        return NULL;
    }
    
    new_cbuff->data = (char*)new_cbuff + sizeof(cbuff_t);
    new_cbuff->capacity = capacity;
    new_cbuff->size = 0;
    new_cbuff->read_idx = 0;

    return new_cbuff;    
}

void CBuffDestroy(cbuff_t* cbuff)
{
    free(cbuff);
    cbuff = NULL;
}

size_t CBuffCapacity(const cbuff_t* cbuff)
{
    return cbuff->capacity;
}

int CBuffIsEmpty(const cbuff_t* cbuff)
{
    return cbuff->size == 0;
}

size_t CBuffFreeSpace(const cbuff_t* cbuff)
{
    return cbuff->capacity - cbuff->size;
}

ssize_t CBuffRead(cbuff_t* cbuff, void *dest, size_t nbytes)
{
    size_t first_copy = 0;
    size_t second_copy = 0;

    if (!dest || !cbuff)
    {
        return -1;
    }

    first_copy = MIN(cbuff->capacity - cbuff->read_idx,
                            MIN(nbytes, cbuff->size));

    memcpy(dest, &(cbuff->data)[cbuff->read_idx], first_copy);
    
    nbytes -= first_copy;
    cbuff->size -= first_copy;
    cbuff->read_idx += first_copy;
    cbuff->read_idx %= cbuff->capacity;
    dest = (char*)dest + first_copy;

    second_copy = MIN(nbytes, cbuff->size);
    memcpy(dest, &(cbuff->data)[cbuff->read_idx], second_copy);

    cbuff->size -= second_copy;
    cbuff->read_idx += second_copy;

    return first_copy + second_copy;
}

ssize_t CBuffWrite(cbuff_t* cbuff, const void *src, size_t nbytes)
{
    size_t first_copy = 0;
    size_t second_copy = 0;

    if (!src || !cbuff)
    {
        return -1;
    }

    first_copy = MIN(cbuff->capacity - (cbuff->read_idx + cbuff->size),
                            MIN(nbytes, CBuffFreeSpace(cbuff)));

    memcpy(&(cbuff->data)[(cbuff->read_idx + cbuff->size) % cbuff->capacity],
           src, first_copy);

    nbytes -= first_copy;
    cbuff->size += first_copy;
    src = (char*)src + first_copy;

    second_copy = MIN(nbytes, CBuffFreeSpace(cbuff));
    
    memcpy(&(cbuff->data)[(cbuff->read_idx + cbuff->size) % cbuff->capacity],
           src, second_copy);

    cbuff->size += second_copy;
  
    return first_copy + second_copy;
}























