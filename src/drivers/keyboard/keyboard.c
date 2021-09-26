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
#include <debug/qemu.h>

void keyboard_init(void)
{
  /* Enable the keyboard */
  outb(0x64, 0x60);
  outb(0x60, 0x47);
  
  qemu_success("Keyboard initialized\r\n");
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
