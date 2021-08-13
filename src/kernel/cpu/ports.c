/**
 * @file ports.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.1
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <kernel/cpu/ports.h>

uint8 inb(uint16 port)
{
  uint8 ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
  return ret;
}

void outb(uint16 port, uint8 data)
{
  asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
}

uint16 inw(uint16 port)
{
  uint16 ret;
  asm volatile("in %%dx, %%ax" : "=a"(ret) : "d"(port));
  return ret;
}


void outw(uint16 port, uint16 data)
{
  asm volatile("out %0, %1" : "=a"(data) : "d"(port));
}

uint8 in8(uint16 port)
{
  uint8 ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

void out8(uint16 port, uint8 data)
{
  asm volatile("outb %0, %1" ::"a"(data), "Nd"(port));
}

uint16 in16(uint16 port)
{
  uint16 ret;
  asm volatile("inw %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

void out16(uint16 port, uint16 data)
{
  asm volatile("outw %0, %1" ::"a"(data), "Nd"(port));
}