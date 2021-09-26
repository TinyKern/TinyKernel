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

struct regs
{
    size_t r15;
    size_t r14;
    size_t r13;
    size_t r12;
    size_t rbp;
    size_t rbx;
    size_t r11;
    size_t r10;
    size_t r9;
    size_t r8;
    size_t rax;
    size_t rcx;
    size_t rdx;
    size_t rsi;
    size_t rdi;
    size_t orig_rax;
    size_t rip;
    size_t cs;
    size_t eflags;
    size_t rsp;
    size_t ss;
    size_t fs_base;
    size_t gs_base;
    size_t ds;
    size_t es;
    size_t fs;
    size_t gs;
    size_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
};

typedef struct regs regs_t;

// extern void cpuid(uint32_t value, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx);
extern void cpuid_info();

#endif // CPU_H