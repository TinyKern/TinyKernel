/**
 * @file string.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.3
 * @date 2021-07-29
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef STRING_H
#define STRING_H

#include <types.h>

/**
* @brief Gets the length of provided string
* @param str - The string to get the length of
*/
uint32_t  strlen(const char*);

/**
 * @brief Compares two strings
 * @param s1 - The 1st string.
 * @param s2 - The 2nd string to compare to s1.
 */
int     strcmp(const char*, const char*);

const char *strchr(const char*, char);
char*   strtok(char*, const char*);
#endif // STRING_H