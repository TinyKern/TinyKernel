/**
 * @file video.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.2
 * @date 2021-07-06
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <drivers/video/video.h>
#include <drivers/vga/vga.h>
#include <kernel/cpu/ports.h>

int get_offset(int col, int row);

int get_cursor_offset()
{
	outb(CTRL_SCREEN_REG, 14);
	int off = inb(DATA_SCREEN_REG) << 8; // High byte: << 8
	outb(CTRL_SCREEN_REG, 15);
	off += inb(DATA_SCREEN_REG);

	return off * 2; // Position * size of char cell
}

void set_cursor_offset(int offset)
{
	offset /= 2;
	outb(CTRL_SCREEN_REG, 14);
	outb(DATA_SCREEN_REG, (uint8_t)(offset >> 8));
	outb(CTRL_SCREEN_REG, 15);
	outb(DATA_SCREEN_REG, (uint8_t)(offset & 0xff));
}

void clear_screen()
{
	for (int col = 0; col < VGA_COLS; col++)
	{
		for (int row = 0; row < VGA_ROWS; row++)
		{
			vga_put_entry(vga_create_entry(' ', vga_create_color(BLACK, BLACK)), col, row);
		}
	}

	vga_set_default_color(vga_create_color(BLACK, GREY));
	set_cursor_offset(get_offset(0, 0));
}

int get_offset(int col, int row) { return 2 * (row * VGA_COLS + col); }