/**
 * @file kernel.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.4
 * @date 2021-07-06
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <drivers/keyboard/keyboard.h>
#include <drivers/vga/vga.h>
#include <kernel/kernel.h>
#include <kernel/stdio.h>
#include <kernel/errno.h>
#include <sys/utils.h>

#define TEST_PANIC TRUE

void input()
{
  char ch = 0;
  char keycode = 0;
  do {
    keycode = get_input_keycode();
    if (keycode == KEY_ENTER)
    {
      vga_putchar('\n');
    }
    else
    {
      ch = get_ascii_char(keycode);
      vga_putchar(ch);
    }
    sleep(0x03FFFFFF);
  } while (ch > 0);
}

void kernel_entry()
{
  // First init vga
  vga_init();

  kprint("Hello World!\n");
  kprintf("%d", 123456789);
  vga_set_default_color(vga_create_color(BLUE, RED));
  kprint("\nGoodbye World!");

  if (TEST_PANIC)
    kpanic(10, "Test Error Message", FALSE);
  
  input();
}
