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

#include "cursor.h"

#define VGA_ADDRESS 0xB8000
#define VGA_COLS 80
#define VGA_ROWS 25

struct vga_entry_t {
  uint8_t ch;
  uint8_t color;
};

// color

extern uint8_t vga_create_color(uint8_t bg, uint8_t fg);
extern void vga_set_default_color(uint8_t color);

// entry

extern struct vga_entry_t vga_create_entry(uint8_t ch, uint8_t color);
extern void vga_put_entry(struct vga_entry_t, size_t x, size_t y);
extern void vga_write_string(const char* str, size_t x, size_t y);
extern bool vga_init();

// output

extern void vga_putchar(const char c);
extern uint32_t draw(uint32_t x, uint32_t y, uint8_t color);

extern void set_buffer_position(size_t x, size_t y);

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
