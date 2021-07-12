/**
 * @file vga.c
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

#include <sys/vga.h>

size_t VGA_COL;
size_t VGA_ROW;
uint8 VGA_DEF_COLOR;
struct vga_entry_t* VGA_BUFFER;

uint8 vga_create_color(uint8 bg, uint8 fg) {
  return (bg << 4) | fg;
}

void vga_set_default_color(uint8 color) {
  VGA_DEF_COLOR = color;
}

struct vga_entry_t vga_create_entry(uint8 ch, uint8 color) {
  return (struct vga_entry_t){ ch, color };
}

void vga_put_entry(struct vga_entry_t entry, size_t x, size_t y) {
  VGA_BUFFER[y * VGA_WIDTH + x] = entry;
}

void vga_init() {
  VGA_COL = 0;
  VGA_ROW = 0;
  VGA_DEF_COLOR = vga_create_color(BLACK, GREY);
  VGA_BUFFER = (struct vga_entry_t*) VGA_ADDRESS;
}

void vga_putchar(const char c) {
  if(c == '\n') {
    VGA_COL = 0;
    ++VGA_ROW;
  } else {
    vga_put_entry(vga_create_entry(c, VGA_DEF_COLOR), VGA_COL, VGA_ROW);
    if(++VGA_COL == VGA_WIDTH) {
      VGA_COL = 0;
      ++VGA_ROW;
    }
  }
}

