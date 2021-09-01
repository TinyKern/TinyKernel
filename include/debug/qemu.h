/**
 * @file qemu.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.1
 * @date 2021-08-22
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef QEMU_H
#define QEMU_H

#include <config.h>

#include <kernel/cpu/ports.h>
#include <stdarg.h>
#include <types.h>

void qemu_puthex(uint32_t i);
void qemu_printf(char* fmt, ...);

void qemu_dbg(char *fmt, ...);
void qemu_success(char *fmt, ...);
void qemu_info(char *fmt, ...);
void qemu_error(char* fmt, ...);
void qemu_panic(char* fmt, ...);

#endif // QEMU_H