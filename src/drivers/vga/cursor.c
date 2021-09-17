/**
 * @file cursor.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.2
 * @date 2021-08-19
 *
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */


#include <drivers/vga/cursor.h>
#include <kernel/cpu/cpu.h>
#include <cdefs.h>

uint8_t cursor_x = 0;
uint8_t cursor_y = 0;

static void update_cursor_position(void)
{
    uint16_t cursor_location;

    /* Get the location of the cursor as a flat array index */
    cursor_location = (cursor_y * 80) + cursor_x;

    /* Send the high cursor byte */
    outb(0x3D4, 14);
    outb(0x3D5, (cursor_location >> 8));

    /* Send the low cursor byte. */
    outb(0x3D4, 15);
    outb(0x3D5, cursor_location);
}

void move_cursor(uint8_t x, uint8_t y)
{
    uint8_t dest_x;
    uint8_t dest_y;

    dest_x = MIN(x, 80);
    dest_y = MIN(y, 25);

    cursor_x = dest_x;
    cursor_y = dest_y;
    update_cursor_position();
}

void enable_cursor(uint8_t start, uint8_t end)
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | start);

    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | end);
}
