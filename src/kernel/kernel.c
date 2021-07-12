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

#include <kernel/kernel.h>
#include <kernel/keyboard.h>
#include <sys/utils.h>
#include <sys/vga.h>

// Fore & Back color values

// digit ascii code for printing integers
int digit_ascii_codes[10] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};

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

void kprint(const char* str) {
  while(*str) {
    vga_putchar(*str);
    ++str;
  }
}

void kernel_entry()
{
  // First init vga
  vga_init();

  /**
   * @brief Printing "Hello World!\n", "1234456789\n", "Goodbye World!"
   * Call the above function to print something
   * here to change the fore & back color,
   * use VGA_DEF_COLOR = vga_create_color(bg, fg)
   */
  kprint("Hello World!\n");
  char num[11];
  itoa(1234456789, num);
  kprint(num);
  vga_set_default_color(vga_create_color(BLUE, RED));
  kprint("\nGoodbye World!");
  input();
}
