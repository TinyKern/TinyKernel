/**
 * @file panic.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.2
 * @date 2021-08-19
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef PANIC_H
#define PANIC_H

#include <drivers/vga/vga.h>
#include <drivers/video/video.h>

#include "cpu/cpu.h"
#include "stdio.h"

/**
 * @brief Kernel panic for unhandled exceptions
 * 
 * @param errcode 
 * @param errmsg 
 */
extern void kpanic(int errcode, char* errmsg);

#endif // PANIC_H