/**
 * @file stdio.h
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

#ifndef STDIO_H
#define STDIO_H

#include <drivers/keyboard/keyboard.h>
#include <drivers/vga/vga.h>
#include <sys/char.h>
#include <config.h>
#include <types.h>

extern void kprint(const char*);

#endif
