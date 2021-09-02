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

/**
 * @brief Prints a debug message to the QEMU console.
 * 
 * @param fmt 
 * @param ... 
 */
void qemu_dbg(char *fmt, ...);

/**
 * @brief Prints a ssuccess message to the QEMU console.
 * 
 * @param fmt 
 * @param ... 
 */
void qemu_success(char *fmt, ...);

/**
 * @brief Prints a info message to the QEMU console.
 * 
 * @param fmt 
 * @param ... 
 */
void qemu_info(char *fmt, ...);

/**
 * @brief Prints a error message to the QEMU console.
 * 
 * @param fmt 
 * @param ... 
 */
void qemu_error(char* fmt, ...);

/**
 * @brief prints a panic message to the QEMU console.
 * 
 * @param fmt 
 * @param ... 
 */
void qemu_panic(char* fmt, ...);

/**
 * @brief Prints a device message to the QEMU console.
 * 
 * @param fmt 
 * @param ... 
 */
void qemu_device(char* fmt, ...);

#endif // QEMU_H