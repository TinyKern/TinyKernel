/**
 * @file utils.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.3
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <sys/utils.h>
#include <kernel/stdio.h>

uint32 digit_count(int num)
{
  uint32 count = 0;
  if (num == 0)
    return 1;
  while (num > 0)
  {
    count++;
    num = num/10;
  }
  return count;
}

void itoa(int value, char* str)
{
  int dgcount = digit_count(value);
  int index = dgcount - 1;
  char x;
  if (value == 0 && dgcount == 1)
  {
    str[0] = '0';
    str[1] = '\0';
  }
  else
  {
    while (value != 0)
    {
      x = value % 10;
      str[index] = x + '0';
      index--;
      value = value/10;
    }
    str[dgcount] = '\0';
  }
}

char* convert_to_base(unsigned int value, int base)
{
  static char rep[] = "0123456789ABCDEF";
  static char buf[50];
  char *ptr;

  ptr = &buf[49];
  *ptr = '\0';

  do
  {
    *--ptr = rep[value % base];
    value /= base;
  } while (value != 0);

  return (ptr);
}

char*   kernel_arguments[128];
int     kernel_argc = 0;

void init_arg_parser(struct stivale2_struct* bootinfo)
{
  struct stivale2_struct_tag_cmdline* cmdline = 
    (struct stivale2_struct_tag_cmdline*)stivale2_get_tag(bootinfo, STIVALE2_STRUCT_TAG_CMDLINE_ID);

  char* args = (char*)cmdline->cmdline;

  kernel_arguments[kernel_argc] = strtok(args, " ");
  while (kernel_arguments[kernel_argc])
  {
    kernel_argc++;
    kernel_arguments[kernel_argc] = strtok(args, " ");
  }
}

int arg_exist(char* arg)
{
  for (int i = 0; i < kernel_argc; i++)
  {
    if (!strcmp(arg, kernel_arguments[i]))
      return 1;
  }
  return 0;
}

void print_args()
{
  kprint("Kernel Arguments: ");
  for (int i = 0; i < kernel_argc; i++)
  {
    kprintf("%s ", kernel_arguments[i]);
  }
  kprint("\n");
}