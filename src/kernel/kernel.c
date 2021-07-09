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

/*
Increase vga_index by width of row(80)
*/
void print_new_line()
{
  if (next_line_index >= 55) 
  {
    next_line_index = 0;
    clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color, next_line_index, vga_index);
  }
  vga_index = 80 * next_line_index;
  next_line_index++;
}

// Assign ascii character to video buffer
void print_char(char ch)
{
  vga_buffer[vga_index] = vga_entry(ch, g_fore_color, g_back_color);
  vga_index++;
}

// Print string is calling print_char
void print_string(char *str)
{
  uint32 index = 0;
  while (str[index])
  {
    print_char(str[index]);
    index++;
  }
}

// Print int by converting it into string
// then print string
void print_int(int num)
{
  char str_num[digit_count(num)+1];
  itoa(num, str_num);
  print_string(str_num);
}

void input()
{
  char ch = 0;
  char keycode = 0;
  do {
    keycode = get_input_keycode();
    if (keycode == KEY_ENTER)
    {
      print_new_line();
    }
    else
    {
      ch = get_ascii_char(keycode);
      print_char(ch);
    }
    sleep(0x04FFFFFF);
  } while (ch > 0);
}

void kernel_entry()
{
  // First init vga with fore & back colors
  init_vga(WHITE, BLACK, next_line_index, vga_index);

  /**
   * @brief Printing "Hello World!\n", "1234456789\n", "Goodbye World!"
   * Call the above function to print something
   * here to change the fore & back color,
   * assign g_fore_color & g_back_color to color values
   *  g_fore_color = BRIGHT_RED;
   */
  print_string("Hello World!");
  print_new_line();
  g_fore_color = BRIGHT_GREEN;
  print_int(123456789);
  default_colors();
  print_new_line();
  print_string("Goodbye World!");
  print_new_line();
  print_string("Type here, one key per second, ENTER to go to next line");
  print_new_line();
  input();
}
