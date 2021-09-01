/**
 * @file cursor.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.0
 * @date 2021-08-19
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef CURSOR_H
#define CURSOR_H

#include "vga.h"
#include <types.h>

extern void enable_cursor(uint8_t start, uint8_t end);
extern void disable_cursor();

#endif // CURSOR_H
