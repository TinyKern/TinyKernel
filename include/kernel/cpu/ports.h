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

extern uint8 inb(uint16 port);
extern void outb(uint16 port, uint8 data);
extern uint16 inw(uint16 port);
extern void outw(uint16 port, uint16 data);
extern uint8 in8(uint16 port);
extern void out8(uint16 port, uint8 data);
extern uint16 in16(uint16 port);
extern void out16(uint16 port, uint16 data);

#endif
