/**
 * @file ports.h
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

#ifndef KERNEL_CPU_H
#define KERNEL_CPU_H

#include <types.h>

extern uint8_t inb(uint16_t port);
extern void outb(uint16_t port, uint8_t data);
extern uint16_t inw(uint16_t port);
extern void outw(uint16_t port, uint16_t data);
extern uint8_t in8(uint16_t port);
extern void out8(uint16_t port, uint8_t data);
extern uint16_t in16(uint16_t port);
extern void out16(uint16_t port, uint16_t data);

#endif
