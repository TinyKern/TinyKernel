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

#include <drivers/vga/vga.h>
#include <debug/qemu.h>

size_t VGA_COL;
size_t VGA_ROW;
uint8_t VGA_DEF_COLOR;
struct vga_entry_t* VGA_BUFFER;

uint8_t vga_create_color(uint8_t bg, uint8_t fg) {
  return (bg << 4) | fg;
}

void vga_set_default_color(uint8_t color) {
  VGA_DEF_COLOR = color;
}

struct vga_entry_t vga_create_entry(uint8_t ch, uint8_t color)
{ return (struct vga_entry_t){ ch, color }; }

void vga_put_entry(struct vga_entry_t entry, size_t x, size_t y)
{
  VGA_BUFFER[y * VGA_COLS + x] = entry;
}

void vga_write_string(const char* str, size_t x, size_t y)
{
  for (size_t i = 0; str[i] != '\0'; i++)
  {
    vga_put_entry(vga_create_entry(str[i], VGA_DEF_COLOR), x + i, y);
  }
}

void vga_set_pixel(uint32_t x, uint32_t y, uint8_t color)
{
  vga_put_entry(vga_create_entry(' ', color), x, y);
}

uint32_t draw(uint32_t x, uint32_t y, uint8_t color)
{
  vga_set_pixel(x, y, color);
  return (x /= y);
}

void vga_init()
{
  VGA_COL = 0;
  VGA_ROW = 0;
  VGA_DEF_COLOR = vga_create_color(BLACK, GREY);
  VGA_BUFFER = (struct vga_entry_t*) VGA_ADDRESS;
  
  qemu_success("VGA initialized, buffer->%p\r\n", VGA_BUFFER);
}

void vga_putchar(const char c) {
  if (c == '\n')
  {
    VGA_COL = 0;
    ++VGA_ROW;
  }
  else if (c == '\r')
  {
    VGA_COL = 0;
  }
  else if (c == '\t')
  {
    VGA_COL += 4;
  }
  else
  {
    vga_put_entry(vga_create_entry(c, VGA_DEF_COLOR), VGA_COL, VGA_ROW);
    if(++VGA_COL == VGA_COLS)
    {
      VGA_COL = 0;
      ++VGA_ROW;
    }
  }
}

void set_buffer_position(size_t x, size_t y)
{
  VGA_COL = x;
  VGA_ROW = y;
}
