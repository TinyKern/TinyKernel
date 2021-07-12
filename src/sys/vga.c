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

uint8 g_fore_color = WHITE;
uint8 g_back_color = BLACK;

uint32 vga_index;
uint16* vga_buffer = NULL;

/*
 * 16 bit video buffer elements(register ax)
 * 8 bits(ah) higher :
 *      lower 4 bits - foreground color
 *      higher 4 bits - back color
 * 8 bits(al) lower :
 *      8 bits : ASCII character to print
 * */
uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color)
{
  uint16 ax = 0;
  uint8 ah = 0, al = 0;

  ah = back_color;
  ah <<= 4;
  ah |= fore_color;
  ax = ah;
  ax <<= 8;
  al = ch;
  ax |= al;

  return ax;
}

// Clears video buffer array
void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color)
{
  uint32 i;
  for(i = 0; i < BUFSIZE; i++)
  {
    (*buffer)[i] = vga_entry(NULL, fore_color, back_color);
  }
}

// Initialize vga buffer
void init_vga(uint8 fore_color, uint8 back_color)
{
  vga_buffer = (uint16*)VGA_ADDRESS; // vga_buffer pointer to VGA_ADDRESS
  clear_vga_buffer(&vga_buffer, fore_color, back_color);
  g_fore_color = fore_color;
  g_back_color = back_color;
}

// Sets g_fore/back_color back to default (WHITE, BLACK)
void vga_default_colors()
{
  g_fore_color = WHITE;
  g_back_color = BLACK;
}