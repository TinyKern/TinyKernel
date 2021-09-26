/**
 * @file keyboard.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.2
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <drivers/keyboard/keyboard.h>
#include <kernel/cpu/ports.h>
#include <kernel/cpu/isr/isr.h>
#include <debug/qemu.h>

char keyboard_map[128] = {
	0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
	'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0,	/* left control */
	 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
	'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0,
	0, 	/* left alt */
	' ',
	0,	/* caps lock */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* F1 ... F10 */
	0, 	/* num lock */
	0,	/* scroll lock */
	0,	/* home key */
	0,	/* up arrow key */
	0,	/* page up */
	'-',
	0,	/* left arrow key */
	0,
	0,	/* right arrow key */
	'+',
	0,	/* end key */
	0,	/* down arrow key */
	0,	/* page down */
	0,	/* insert key */
	0,	/* delete key */
	0,   0,   0,
	0, 	/* F11 key */
	0,	/* F12 key */
	0,	/* All other keys are undefined */
};

void keyboard_handler(register_t *reg)
{
	uint8_t i, scancode;

	/* Get the scancode */
	for (i = 1000; i > 0; i++)
	{
		/* Check if scan code is ready */
		if ((inb(0x64) & 0x1) == 0) continue;

		/* Read the scancode */
		scancode = inb(0x60);
		break;
	}

	if (i > 0)
	{
		if (scancode & 0x80)
		{ /* Key release */ }
		else
		{
			/* Key down */
			qemu_dbg("Key Pressed %c\r\n", keyboard_map[scancode]);
		}
	}
}

void keyboard_init(void)
{
	register_interrupt_handler(IRQ_BASE + 1, keyboard_handler);

	qemu_success("Keyboard Loaded\r\n");
}

char get_input_keycode()
{
	char ch = 0;
	while ((ch = inb(KEYBOARD_PORT)) != 0x60)
	{
		if (ch > 0)
			return ch;
	}
	return ch;
}
