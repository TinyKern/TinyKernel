/**
 * @file utils.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.3
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef UTILS_H
#define UTILS_H

#include <kernel/stivale2.h>
#include <types.h>

#include "string.h"

extern uint32   digit_count(int);

/**
* @brief Converts a int to a string
* @param value - The value to convert
* @param str - The string to write to
*/
extern void     itoa(int, char*);

/**
* @brief Converts a number into a base string
* @param value - The number to convert
* @param base - The base to convert the number to
*/
extern char*    convert_to_base(unsigned int, int);

void init_arg_parser(struct stivale2_struct* bootinfo);
int arg_exist(char*);
void print_args();

#endif
