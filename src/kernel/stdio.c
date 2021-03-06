/**
 * @file stdio.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.6
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <kernel/stdio.h>
#include <kernel/errno.h>
#include <sys/utils.h>

// TODO: Make the stdarg header file without using the real libc version
#include <stdarg.h>

void __kprint(const char* str)
{
  while(*str)
  {
    vga_putchar(*str);
    ++str;
  }
}