/**
 * @file stdio.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.5
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

/**
 * @brief Prints a string on the screen
 * @param str - The string to print
 */
extern void __kprint(const char*);
#define kprint(...) __kprint(__VA_ARGS__)

/**
 * @brief Prints a format string to the kernel console
 * @param fmt Format string
 * @param %c - print a char
 * @param %d - print a decimal number
 * @param %o - print a octal number
 * @param %s - print a string
 * @param %x - print a hexadecimal number
 */
extern void __kprintf(char*, ...);
#define kprintf(...) __kprintf(__VA_ARGS__)

#endif
