#ifndef _FSALLOC_H_
#define _FSALLOC_H_

/* version 0.0 */
/* date 23.09.19 */
/* time 12:30 */

#include <stddef.h> /*size_t*/

typedef struct allocator allocator_t;

/*O(1) 
block_size - the size of each unit in bytes
num_of_block - the max num of memomry blocks
return- the total size is needed to allocate by the user in bytes
*/
size_t FSASuggestSize(size_t block_size, size_t num_of_blocks);

/*O(1)
dest- the begining of the segment that allocated by the user
block_size- the size of each unit in bytes
total_size- the total size allocated by the user in bytes
return- the begining of the segment that allocated. return null if the total size too small
*/
allocator_t* FSAInit(void* dest, size_t block_size, size_t total_size);

/* O(1)
allocator- in which segment do allocation
return- the address of the allocated block, if full return NULL
*/ 
void* FSAAlloc(allocator_t *allocator);

/*O(1)
block- the address of the block to free
*/
void FSAFree(void *block);

/*O(n)/O(1)
allocator- which segment
return num of free blocks */
size_t FSACountFree(const allocator_t *allocator);

#endif
