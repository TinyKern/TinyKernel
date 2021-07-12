/**
 * @file vga.h
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

#ifndef VGA_H
#define VGA_H

#include "types.h"
#include <config.h>

#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

extern uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color);
extern void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color);
extern void init_vga(uint8 fore_color, uint8 back_color);
extern void vga_default_colors();

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