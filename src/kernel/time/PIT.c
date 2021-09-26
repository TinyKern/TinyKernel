/**
 * @file PIT.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.1
 * @date 2021-08-24
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */


#include <kernel/time/PIT.h>
#include <kernel/stdio.h>
#include <debug/qemu.h>
#include <system.h>

void pit_init(uint32_t frequency)
{
    uint32_t divisor = 1193180 / frequency;

    outb(0x43, 0x36);
    outb(0x40, (uint8_t)divisor & 0xFF);
    outb(0x40, (uint8_t)(divisor >> 8) & 0xFF);

    qemu_success("PIT Loaded, %uHz\r\n", frequency);
}

volatile uint64_t pit_ticks = 0;

void pit_add_tick()
{
    pit_ticks++;
    outb(0x20, 0x20);
}

void pit_add_ticks(uint64_t ticks)
{
    pit_ticks += ticks;
    outb(0x20, 0x20);
}

uint64_t pit_get_ticks()
{ return pit_ticks; }

unsigned read_pit_count(void)
{
    unsigned count = 0;

    // Disables interrupts
    cli();

    outb(0x43, 0b0000000);

    // Reads the count
    count = inb(0x40);          // Low byte
    count |= inb(0x40) << 8;    // High byte

    return count;
}

void set_pit_count(unsigned count)
{
    // Disables interrupts
    cli();

    // Set low byte
    outb(0x40, count & 0xFF);
    outb(0x40, (count & 0xFF00) >> 8);
    return;
}
