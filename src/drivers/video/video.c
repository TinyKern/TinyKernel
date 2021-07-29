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
	outb(DATA_SCREEN_REG, (uint8)(offset >> 8));
	outb(CTRL_SCREEN_REG, 15);
	outb(DATA_SCREEN_REG, (uint8)(offset & 0xff));
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