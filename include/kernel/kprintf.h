/**
 * @file kprintf.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.2
 * @date 2021-08-11
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef KPRINTF_H
#define KPRINTF_H

extern int __kprintf(char *fmt, ...);

/**
 * @brief Prints a format string to the kernel console
 * @param fmt Format string
 * @param %c - print a char
 * @param %d - print a decimal number
 * @param %o - print a octal number
 * @param %s - print a string
 * @param %x - print a hexadecimal number
 */
#define kprintf(...) __kprintf(__VA_ARGS__)

#endif // KPRINTF_H