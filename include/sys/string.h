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
 * @brief Get the length of a string.
 * 
 * @param str The string to get the length of.
 * 
 * @return uint32_t - The length of the string.
 */
uint32_t strlen(const char*);

/**
 * @brief Compares two strings
 * 
 * @param s1 - The 1st string.
 * @param s2 - The 2nd string to compare to s1.
 * 
 * @return int - 0 if the strings are equal, -1 if s1 is less than s2, 1 if s1 is greater than s2.
 */
int strcmp(const char*, const char*);

/**
 * @brief Locates a char in a string
 * 
 * @param src - The string to search in.
 * @param chr - The char to search for.
 * 
 * @return const char* - The char if found, NULL otherwise.
 */
const char *strchr(const char*, char);

/**
 * @brief Tokenizes a string
 * 
 * @param str - The string to tokenize
 * @param delim - The delimiter to use
 * 
 * @return char* - The tokenized string or NULL if no tokens were found.
 */
char *strtok(char*, const char*);

/**
 * @brief Copies <n> bytes from <src> to <dest>
 * 
 * @param dest 
 * @param src 
 * @param size 
 * @return void* - The destination pointer where the copy ended.
 */
void *memcpy(void* dest, const void* src, uint32_t size);

/**
 * @brief Copies the string <src> to <dest>
 * 
 * @param dest 
 * @param src 
 * @return char* - The destination pointer where the string was copied to.
 */
char *strcpy(char* dest, const char* src);

/**
 * @brief Concatenates <src> to <dest>
 * 
 * @param dest 
 * @param src 
 * @return char* - The destination pointer where the string was concatenated to.
 */
char *strcat(char* dest, const char* src);
#endif // STRING_H