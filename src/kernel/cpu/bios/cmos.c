/**
 * @file cmos.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.0
 * @date 2021-08-15
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <kernel/cpu/bios/cmos.h>
#include <kernel/cpu/cpu.h>

uint8_t cmod_lowmem()
{
    uint8_t lowmem;

    // Get the low memory size from CMOS
    outb(0x70, 0x30);
    lowmem = inb(0x71);
    return lowmem;
}

uint8_t cmod_highmem()
{
    uint8_t highmem;

    // Get the high memory size from CMOS
    outb(0x70, 0x31);
    highmem = inb(0x71);
    return highmem;
}

uint16_t cmod_totalmem()
{
    uint16_t totalmem;
    uint8_t lowmem, highmem;

    lowmem = cmod_lowmem();
    highmem = cmod_highmem();

    // Calculate the total memory size
    totalmem = lowmem | highmem << 8;
    return totalmem;
}
