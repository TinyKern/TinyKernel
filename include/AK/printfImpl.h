#ifndef PRINTF_IMPL_H
#define PRINTF_IMPL_H

#include <drivers/vga/vga.h>
#include <kernel/errno.h>
#include <kernel/stdio.h>
#include <sys/utils.h>
#include <stdarg.h>
#include <types.h>

int printf_internal(char *fmt, va_list arg)
{
  unsigned int i;
  char* position;
  char* s;

  for (position = fmt; *position != '\0'; position++)
  {
    if (*position == '%')
    {
      position++;

      switch (*position)
      {
      case 'c':
        i = va_arg(arg, int);
        if (i == 0)
        {
          kpanic(0x0116, "kprintf: Invalid argument: \"%c\"", FALSE);
          break;
        }
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
        if (s == 0)
        {
          kpanic(0x0117, "kprintf: Invalid argument: \"%s\"", FALSE);
          break;
        }
        kprint(s);
        break;

      case 'x':
        i = va_arg(arg, unsigned int);
        kprint(convert_to_base(i, 16));
        break;
      }
    }
    else
    {
      switch (*position)
      {
      case '\n':
        vga_putchar('\n');
        break;

      case '\r':
        vga_putchar('\r');
        break;

      case '\t':
        vga_putchar('\t');
        break;
      
      case '\b':
        vga_putchar('\b');
        break;

      case '\f':
        vga_putchar('\f');
        break;

      case '\v':
        vga_putchar('\v');
        break;
      
      default:
        vga_putchar(*position);
        break;
      }
    }
  }

  return i;
}

#endif // PRINTF_IMPL_H