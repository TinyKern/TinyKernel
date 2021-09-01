/**
 * @file memory.c
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


#include <kernel/syscalls/syscalls.h>
#include <kernel/memory.h>
#include <kernel/stdio.h>

MemorySegmentHeader* first_free_segment;

void heap_init(uint64_t heap_address, uint64_t heap_size)
{
    first_free_segment = (MemorySegmentHeader*)heap_address;
    first_free_segment->length = heap_size - sizeof(MemorySegmentHeader);
    first_free_segment->next = NULL;
    first_free_segment->prev = NULL;
    first_free_segment->next_free = NULL;
    first_free_segment->prev_free = NULL;
    first_free_segment->free = true;
}

void* kmalloc(size_t size)
{
    size_t remainder = size % 8;
    size -= remainder;
    if (remainder != 0) size += 8;

    MemorySegmentHeader* current_segment = first_free_segment;

    while (true)
    {
        if (current_segment->length >= size)
        {
            if (current_segment->length > size + sizeof(MemorySegmentHeader))
            {
                MemorySegmentHeader* new_segment = (MemorySegmentHeader*)((uint64_t)current_segment + sizeof(MemorySegmentHeader) + size);
                
                new_segment->free = true;
                new_segment->length = ((uint64_t)current_segment->length) - (sizeof(MemorySegmentHeader) + size);
                new_segment->next = current_segment->next;
                new_segment->prev = current_segment;
                new_segment->next_free = current_segment->next_free;
                new_segment->prev_free = current_segment->prev_free;

                current_segment->next_free = new_segment;
                current_segment->next = new_segment;
                current_segment->length = size;
            }

            if (current_segment == first_free_segment)
                first_free_segment = current_segment->next_free;

            current_segment->free = false;

            if (current_segment->prev_free != NULLPTR)
                current_segment->prev_free->next_free = current_segment->next_free;

            if (current_segment->next_free != NULLPTR)
                current_segment->next_free->prev_free = current_segment->prev_free;

            if (current_segment->prev != NULLPTR)
                current_segment->prev->next_free = current_segment->next_free;

            if (current_segment->next != NULLPTR)
                current_segment->next->prev_free = current_segment->prev_free;

            return current_segment + 1;
        }

        // Should never happen, but if does, no memory remaining
        if (current_segment->next_free == NULLPTR)
            return 0;

        current_segment = current_segment->next_free;
    }

    return 0; // Should never get here
}

void combine_free(MemorySegmentHeader* segment_a, MemorySegmentHeader* segment_b)
{
    if (segment_a == NULLPTR || segment_b == NULLPTR) return;

    if (segment_a < segment_b)
    {
        segment_a->length += segment_b->length + sizeof(MemorySegmentHeader);
        segment_a->next = segment_b->next;
        segment_a->next_free = segment_b->next_free;
        segment_b->prev = segment_a;
        segment_b->next->prev_free = segment_a;
        segment_b->next_free->prev_free = segment_a;
    }
    else
    {
        segment_b->length += segment_a->length + sizeof(MemorySegmentHeader);
        segment_b->next = segment_a->next;
        segment_b->next_free = segment_a->next_free;
        segment_a->prev = segment_b;
        segment_a->next->prev_free = segment_b;
        segment_a->next_free->prev_free = segment_b;
    }
}

void kfree(void* ptr)
{
    MemorySegmentHeader* current_segment = ((MemorySegmentHeader*)ptr) - 1;
    current_segment->free = true;

    if (current_segment < first_free_segment)
        first_free_segment = current_segment;
    
    if (current_segment->next_free != NULLPTR)
        if (current_segment->next_free->prev_free < current_segment)
            current_segment->next_free->prev_free = current_segment;
    if (current_segment->prev_free != NULLPTR)
        if (current_segment->prev_free->next_free > current_segment)
            current_segment->prev_free->next_free = current_segment;

    if (current_segment->next != NULLPTR)
    {
        current_segment->next->prev = current_segment->prev_free;
        if (current_segment->next->free)
            combine_free(current_segment, current_segment->next);
    }
    if (current_segment->prev != NULLPTR)
    {
        current_segment->prev->next = current_segment->next_free;
        if (current_segment->prev->free)
            combine_free(current_segment->prev, current_segment);
    }
}