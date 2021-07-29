#ifndef STRING_H
#define STRING_H

#include <types.h>

/**
* @brief Gets the length of provided string
* @param str - The string to get the length of
*/
uint32  strlen(const char*);

/**
 * @brief Compares two strings
 * @param s1 - The 1st string.
 * @param s2 - The 2nd string to compare to s1.
 */
int     strcmp(const char*, const char*);

const char *strchr(const char*, char);
char*   strtok(char*, const char*);
#endif // STRING_H