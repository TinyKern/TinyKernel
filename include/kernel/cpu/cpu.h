/**
 * @file cpu.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.3
 * @date 2021-08-12
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef CPU_H
#define CPU_H

#include <types.h>
#include "ports.h"

#define LSW(x) ((uint32)(x)&0xFFFF)
#define MSW(x) (((uint32)(x) >> 16) & 0xFFFF)
#define LSB(x) ((x)&0xFF)
#define MSB(x) (((x) >> 8) & 0xFF)

#define sti() __asm__ ("sti"::)
#define cli() __asm__ ("cli"::)
#define nop() __asm__ ("nop"::)

#define iret() __asm__ ("iret"::)

extern void cpuid(uint32_t value, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx);
extern void cpuid_info();

#endif // CPU_H