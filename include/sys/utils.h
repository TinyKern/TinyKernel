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

#include <types.h>

#include "string.h"

/**
 * @brief Counts the number of digits in a number
 * 
 * @param num The number to count the digits of
 * 
 * @return uint32_t - Number of digits
 */
extern uint32_t digit_count(int);

/**
* @brief Converts a int to a string
* 
* @param value - The value to convert
* @param str - The string to write to
*/
extern void itoa(int, char*);

/**
* @brief Converts a number into a base string
*
* @param value - The number to convert
* @param base - The base to convert the number to
*
* @return char* - The converted string.
*/
extern char* convert_to_base(unsigned int, int);

#endif // UTILS_H
