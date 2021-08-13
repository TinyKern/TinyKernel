/**
 * @file kernel.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.5
 * @date 2021-07-06
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <drivers/keyboard/keyboard.h>
#include <drivers/video/video.h>
#include <drivers/vga/vga.h>
#include <kernel/syscalls/syscalls.h>
#include <kernel/cpu/cpu.h>
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

int readKey(char key)
{
  char keycode = 0;
  do {
    keycode = get_input_keycode();
  } while (keycode != key);
  return TRUE;
}

void kernel_entry()
{
  // Initialize VGA Driver
  int vga = vga_init();
  clear_screen();

  kprintf("TinyKernel - %s\n", KERNEL_VERSION);
  kprintf(" [i] Kernel Version:   %s\n", KERNEL_VERSION);
  kprintf(" [i] Keyboard Driver:  Enabled\n");
  if (vga == TRUE)
    kprintf(" [i] VGA Driver:       Enabled\n");
  cpuid_test();
  kprintf("\n");
  sys_beep(440);
  kprintf(" Press enter to shut down\n");
  while (TRUE)
  {
    if (readKey(KEY_ENTER) == TRUE)
    {
      sys_shutdown();
    }

  }
}
