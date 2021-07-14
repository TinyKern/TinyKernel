/**
 * @file vga.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.3
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef VGA_H
#define VGA_H

#include <types.h>
#include <config.h>

#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

struct vga_entry_t {
  uint8 ch;
  uint8 color;
};

// color
extern uint8 vga_create_color(uint8 bg, uint8 fg);
extern void vga_set_default_color(uint8 color);

// entry
extern struct vga_entry_t vga_create_entry(uint8 ch, uint8 color);
extern void vga_put_entry(struct vga_entry_t, size_t x, size_t y);
extern void vga_init();

// output
extern void vga_putchar(const char c);

enum vga_color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARK_GREY,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_MAGENTA,
    YELLOW,
    WHITE
};

#endif
