/**
 * @file gdt.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.2
 * @date 2021-08-15
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef GDT_H
#define GDT_H

#include <types.h>

#define NULL_SEGMENT 0
#define CODE_SEGMENT 1
#define DATA_SEGMENT 2

struct GDT
{
    uint16_t  segment_limit;      // segment limit first 0-15 bits
    uint16_t  base_low;           // base first 0-15 bits
    uint8_t   base_middle;        // base 16-23 bits
    uint8_t   access;             // access rights
    uint8_t   granularity;        // high 4 bits (flags) low 4 bits (limit 4 last bits)(limit is 20 bit wide)
    uint8_t   base_high;          // base 24-31 bits
} __attribute__((packed));

struct GDT_PTR
{
    uint16_t      limit_size;     // limit size of all GDT segments
    struct GDT* base_address;   // base address of the first GDT segment
} __attribute__((packed));

extern struct GDT gdt_entries[3];
extern struct GDT_PTR gdt_first;

extern bool gdt_init();

#endif // GDT_H