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

void kernel_entry(/* uint32 magic, struct kernel_args* args */)
{
  // First init vga
  vga_init();

  // if (magic != KERNEL_MAGIC)
  // {
  //   kpanic(ERRNO_KERNEL_INVALID_MAGIC, "Invalid magic number", FALSE);
  // }

  kprintf("Hello World!\n");
  kprintf("my char: %c\n"); // Will print an error because we don't have a char
  kprintf("my string: %s\n", "Hello World!");
  vga_set_default_color(vga_create_color(RED, WHITE));
  kprintf("Goodbye World!\n");

  for(int y =4; y < 5; y++)
    for(int x = 0; x < VGA_WIDTH; x++)
      draw(x, y, 0xFF);
  
  vga_set_default_color(vga_create_color(WHITE, BLACK));
  input();
}
