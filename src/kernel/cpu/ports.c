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

uint8_t inb(uint16_t port)
{
  uint8_t ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
  return ret;
}

void outb(uint16_t port, uint8_t data)
{
  asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
}

uint16_t inw(uint16_t port)
{
  uint16_t ret;
  asm volatile("in %%dx, %%ax" : "=a"(ret) : "d"(port));
  return ret;
}


void outw(uint16_t port, uint16_t data)
{
  asm volatile("out %0, %1" : "=a"(data) : "d"(port));
}

uint8_t in8(uint16_t port)
{
  uint8_t ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

void out8(uint16_t port, uint8_t data)
{
  asm volatile("outb %0, %1" ::"a"(data), "Nd"(port));
}

uint16_t in16(uint16_t port)
{
  uint16_t ret;
  asm volatile("inw %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

void out16(uint16_t port, uint16_t data)
{
  asm volatile("outw %0, %1" ::"a"(data), "Nd"(port));
}

uint32_t in32(uint16_t port)
{
  uint32_t ret;

  asm volatile("inl %w1, %0": "=a"(ret): "d"(port));
  return ret;
}

void out32(uint16_t port, uint32_t data)
{
  asm volatile("outl %0, %w1":: "a"(data), "d"(port));
}