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

void _qemu_dbg(char *fmt, ...);
void _qemu_success(char *fmt, ...);
void _qemu_info(char *fmt, ...);
void _qemu_error(char* fmt, ...);
void _qemu_panic(char* fmt, ...);
void _qemu_device(char* fmt, ...);
void _qemu_warning(char* fmt, ...);

#if CONFIG_QEMU_DEBUG
# define qemu_dbg(fmt, ...) _qemu_dbg(fmt, ##__VA_ARGS__)
# define qemu_success(fmt, ...) _qemu_success(fmt, ##__VA_ARGS__)
# define qemu_info(fmt, ...) _qemu_info(fmt, ##__VA_ARGS__)
# define qemu_error(fmt, ...) _qemu_error(fmt, ##__VA_ARGS__)
# define qemu_panic(fmt, ...) _qemu_panic(fmt, ##__VA_ARGS__)
# define qemu_device(fmt, ...) _qemu_device(fmt, ##__VA_ARGS__)
# define qemu_warning(fmt, ...) _qemu_warning(fmt, ##__VA_ARGS__)
#else
# define qemu_dbg(fmt, ...)
# define qemu_success(fmt, ...)
# define qemu_info(fmt, ...)
# define qemu_error(fmt, ...)
# define qemu_panic(fmt, ...)
# define qemu_device(fmt, ...)
# define qemu_warning(fmt, ...)
#endif /* CONFIG_QEMU_DEBUG */

#endif // QEMU_H