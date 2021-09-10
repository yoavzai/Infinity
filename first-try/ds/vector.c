#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc realloc */
#include <errno.h> /* errno */
#include <string.h> /* strcmp */
#include <assert.h> /* assert */

#include "vector.h"

#define RESET "\x1b[0m"

struct vector
{
    void* head;
    size_t size_of_element;
    size_t size;
    size_t capacity;
    #ifndef NDEBUG
    size_t status;
    #endif
};


#ifndef NDEBUG
int InvalidPointer(const vector_t* vector)
{
    if (vector == NULL || vector->status != 0xDEADBEEF)
    {
        printf(RESET"Ivalid pointer!\n");
        return -1;
    }
    
    return 0;
}
#endif

/***********************************************************************************/

vector_t* VectorCreate(size_t size_of_element, size_t num_of_elements)
{
    vector_t* new_vector;
   
    #ifndef NDEBUG 
	if (num_of_elements == 0 || size_of_element == 0)
	{
		assert(printf(RESET"Can't create a vector of size zero\n"));
		return NULL; 
	}
    #endif  

	new_vector = malloc(sizeof(vector_t));	

	if (new_vector == NULL)
    {
        assert(fprintf(stderr, RESET"Error: %s\n", strerror(errno)));
        return NULL;
    }

    new_vector->head = NULL;
    new_vector->size_of_element = size_of_element;
    new_vector->size = 0;
    new_vector->capacity = num_of_elements;
    #ifndef NDEBUG
    new_vector->status = 0xDEADBEEF;
    #endif
    
    if (VectorReserve(new_vector, new_vector->capacity))
    {
        fprintf(stderr, RESET"Error: %s\n", strerror(errno));
        free(new_vector);

        return NULL;
    }
    
    return new_vector;
}

void VectorDestroy(vector_t* vector)
{
    #ifndef NDEBUG
    if (InvalidPointer(vector))
    {
        return;
    }

    vector->status = 0;
    #endif

    free(vector->head);
    free(vector);
}

size_t VectorSize(const vector_t* vector)
{
    #ifndef NDEBUG
    if (InvalidPointer(vector))
    {
        return 0;
    }
    #endif

    return vector->size;
}

size_t VectorCapacity(const vector_t* vector)
{
    #ifndef NDEBUG
    if (InvalidPointer(vector))
    {
        return 0;
    }
    #endif

    return vector->capacity;
}

int VectorPushBack(vector_t* vector, const void* element)
{
    #ifndef NDEBUG
    if (InvalidPointer(vector))
    {
        return -1;
    }
    #endif

    if (vector->size == vector->capacity)
    {   
        if (VectorReserve(vector, vector->capacity * 2))
        {
            assert(fprintf(stderr, RESET"Error: %s\nVector still active\n", strerror(errno)));
            return 1;
        } 
    }

    memcpy((char*)vector->head + (vector->size) * vector->size_of_element,
            element, vector->size_of_element);
    vector->size += 1;
    
    return 0;         
}


void VectorPopBack(vector_t* vector)
{
    #ifndef NDEBUG
    if (InvalidPointer(vector))
    {
        return;
    }
    #endif
    
    if (vector->size == 0)
    {
        assert(printf(RESET"Nothing to pop, stack is empty\n"));
        return;
    }
    
    vector->size -= 1;

    if (vector->size <= vector->capacity / 4 && vector->size != 0)
    {
        if (VectorReserve(vector, vector->capacity / 2))
        {
            assert(fprintf(stderr, RESET"Error: %s\nVector still active\n", strerror(errno)));
        }   
    }
}

void* VectorGetItemAddress(const vector_t* vector, size_t index)
{
    #ifndef NDEBUG
    if (InvalidPointer(vector))
    {
        return NULL;
    }
    #endif
    
    if (index >= vector->size)
    {
        assert(printf(RESET"Invalid index\n"));
        return NULL;
    }    
    
    return (char*)vector->head + index * vector->size_of_element;    
}

int VectorReserve(vector_t* vector, size_t num_of_elements)
{
    void* old_head;

    #ifndef NDEBUG
    if (InvalidPointer(vector))
    {
        return -1;
    }
    #endif
    
    old_head = vector->head;
    vector->head = realloc(vector->head, num_of_elements * vector->size_of_element);

    if (vector->head == NULL)
        {
            vector->head = old_head;
            return 1;
        }
    vector->capacity = num_of_elements;

    if (vector->size > num_of_elements)
    {
        vector->size = num_of_elements;
    }

    return 0;
}

