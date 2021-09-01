/**
 * @file memory.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.2
 * @date 2021-08-17
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <types.h>

typedef struct MemorySegmentHeader
{
    uint64_t                    length;
    struct MemorySegmentHeader  *next;
    struct MemorySegmentHeader  *prev;
    struct MemorySegmentHeader  *next_free;
    struct MemorySegmentHeader  *prev_free;
    bool                        free;
} MemorySegmentHeader;

#define ALLOC_UNIT 3 * (1024 * 4)

void heap_init(uint64_t heap_address, uint64_t heap_size);

/**
 * @brief Allocate memory for a new memory block
 * @param size The size of the memory block to allocate
 * @return A pointer to the allocated memory block
*/
void* kmalloc(size_t size);

/**
 * @brief Free memory allocated for a memory block
 * @param ptr The pointer to the memory block to free
 * @return A pointer to the memory block
 */
void kfree(void* ptr);

/**
 * @brief Allocate memory memory for an array of nmemb elements
 * @param nmemb The number of elements to allocate
 * @param size The size of each element
 * @return A pointer to the allocated memory block
 */
extern void* kcalloc(size_t nmemb, size_t size);

/**
 * @brief changes the size of a memory block
 * @param ptr The pointer to the memory block
 * @param size The new size of the memory block
 * @return A pointer to the memory block
 * @note This function does not free the memory block
 *             and the new memory block is not zeroed
 * @note This function does not check if the memory block
 *              is already allocated
 */
extern void* krealloc(void* ptr, size_t size);
 

#endif // MEMORY_H
