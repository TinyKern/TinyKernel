/**
 * @file stdio.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.4
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <kernel/stdio.h>
#include <sys/utils.h>

// TODO: Make the stdarg header file without using the real libc version
#include <stdarg.h>

void kprint(const char* str)
{
  while(*str)
  {
    vga_putchar(*str);
    ++str;
  }
}

// FIXME: when entering \n inside of the format string, it doesn't work
// Instead, it just prints a \n with no text
void kprintf(char *fmt, ...)
{
  char *position;
  unsigned int i;
  char *s;

  va_list arg;
  va_start(arg, fmt);

  for (position = fmt; *position != '\0'; position++)
  {
    while (*position != '%')
    {
      vga_putchar(*position);
      position++;
    }

    position++;

    switch (*position)
    {
    case 'c':
      i = va_arg(arg, int);
      vga_putchar(i);
      break;

    case 'd':
    {
      i = va_arg(arg, int);
      if (i < 0)
      {
        i = -i;
        vga_putchar('-');
      }
      
      char i_out[32];
      itoa(i, i_out);
      kprint(i_out);
      break;
    }

    case 'o':
      i = va_arg(arg, unsigned int);
      kprint(convert_to_base(i, 8));
      break;

    case 's':
      s = va_arg(arg, char *);
      kprint(s);
      break;

    case 'x':
      i = va_arg(arg, unsigned int);
      kprint(convert_to_base(i, 16));
      break;
    }
  }
  va_end(arg);
}