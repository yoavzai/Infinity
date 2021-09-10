/****************************************************************
* 																*
* FILE_NAME: hash.c                 			                *
* 																*
* Description: HASH DS                                          *
* 																*
* Date: 13.11.2019												*
* 																*
* Author: Yoav Zaidenberg								    	*
* 																*
* Reviewer: Eliraz Ben-Moshe                                    *
*   								                        	*
* Status: A		                                                *
*									           					*
*****************************************************************/

#include <stddef.h> /* size_t, NULL */
#include <stdlib.h> /* malloc, free */

#include "hash.h"
#include "dlist.h"

/************* Declerations & Globals *****************/

static dlist_iter_t FindIter(hash_t *hash, const void *data);

struct hash
{
    hash_func_t hash_func;
    comp_func_t comp_func;
    size_t nbuckets;
    void* comp_param;
    dlist_t** table;
};

/***************** Utility Funcs ******************/

static dlist_iter_t FindIter(hash_t *hash, const void *data)
{
    dlist_t* bucket = hash->table[hash->hash_func(data)];

    return DListFind(DListBegin(bucket), DListEnd(bucket),
                            hash->comp_func, data);
}

/****************** Create *********************/

hash_t *HTCreate(hash_func_t hash_func, size_t num_of_buckets,
                 comp_func_t comp, void *param)
{
    size_t i = 0;
    hash_t* new_hash = (hash_t*)malloc(sizeof(hash_t) + 
                        sizeof(dlist_t**) * num_of_buckets);

    if (!new_hash)
    {
        return NULL;
    }

    new_hash->table = (dlist_t**)(new_hash + 1);

    for (i = 0; i < num_of_buckets; ++i)
    {
        new_hash->table[i] = DListCreate();

        if (new_hash->table[i] == NULL)
        {
            new_hash->nbuckets = i;
            HTDestroy(new_hash);
            
            return NULL;
        }
    }

    new_hash->hash_func = hash_func;
    new_hash->comp_func = comp;
    new_hash->nbuckets = num_of_buckets;
    new_hash->comp_param = param;

    return new_hash;
}                

/***************** Destroy ******************/

void HTDestroy(hash_t *hash)
{
    size_t i = 0;

    for (i = 0; i < hash->nbuckets; ++i)
        {
            DListDestroy(hash->table[i]);
        }

    free(hash);
    hash = NULL;
}

/***************** Insert ******************/

int HTInsert(hash_t *hash, void *data)
{
    dlist_t* bucket = hash->table[hash->hash_func(data)];

    return DListIsSame(DListPushBack(bucket, data), DListEnd(bucket));
}

/***************** Remove ******************/

void HTRemove(hash_t *hash, const void *data)
{
    DListRemove(FindIter(hash, data));
}

/***************** Find ******************/

void *HTFind(hash_t *hash, const void *data)
{
    dlist_t* bucket = hash->table[hash->hash_func(data)];
    dlist_iter_t found = FindIter(hash, data);

    if (!DListIsSame(found, DListEnd(bucket)))
    {
        DListSplice(DListBegin(bucket), found, DListNext(found));
    }

    return DListGetData(found);
}

/***************** ForEach ******************/

int HTForEach(hash_t *hash, op_func_t op_func,void *param)
{
    size_t i = 0;
    int status = 0;

    while (i < hash->nbuckets && status == 0)
    {
        dlist_t* bucket = hash->table[i];
        status = DListForEach(DListBegin(bucket), DListEnd(bucket),
                 op_func, param);
        ++i;
    }

    return status;
}

/***************** Size ******************/

size_t HTSize(const hash_t *hash)
{
    size_t total_size = 0;
    size_t i = 0;

    for (i = 0; i < hash->nbuckets; ++i)
    {
        total_size += DListSize(hash->table[i]);
    }

    return total_size;
}

/***************** IsEmpty ******************/

int HTIsEmpty(const hash_t *hash)
{
    return HTSize(hash) == 0;
}
