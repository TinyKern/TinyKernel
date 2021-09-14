/**
 * @file string.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.4
 * @date 2021-07-29
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <sys/string.h>

uint32_t strlen(const char *str)
{
  uint32_t length = 0;
  while (str[length])
    length++;
  return length;
}

int strcmp(const char *s1, const char *s2)
{
  while (*s1 == *s2++)
    if (*s1++ == 0)
      return 0;
  return (*(uint8_t*)s1 - *(uint8_t*)--s2);
}

const char *strchr(const char* s, char ch)
{
  while (*s)
  {
    if (*s == ch)
      return s;
    s++;
  }
  return 0;
}

char *strtok(char* s, const char* delim)
{
  static char* old = 0;
  char* word;

  if (!s)
    s = old;

  while (*s && strchr(delim, *s))
    s++;

  if (!*s)
  {
    old = s;
    return 0;
  }

  word = s;
  while (*s && !strchr(delim, *s))
    s++;

  if (*s)
  {
    *s = 0;
    old = s + 1;
  }
  else
  {
    old = s;
  }

  return word;
}

void* memcpy(void* dest, const void* src, uint32_t size)
{
  char* d = dest;
  const char* s = src;
  while (size--)
    *d++ = *s++;
  return dest;
}

int memcmp(const void* ptr1, const void* ptr2, size_t num)
{
  register const uint8_t *s1 = (const uint8_t *)ptr1;
  register const uint8_t *s2 = (const uint8_t *)ptr2;
  while (num-- > 0)
    if (*s1++ != *s2++)
      return s1[-1] < s2[-1] ? -1 : 1;
  return 0;
}

uint8_t *memset(uint8_t *dest, const uint8_t value, size_t length)
{
  uint8_t *temp = dest;
  
  while (length--)
    *temp++ = value;

  return dest;
}

char* strcpy(char* dest, const char* src)
{ return memcpy(dest, src, strlen(src) + 1); }

char* strcat(char* dest, const char* src)
{
  strcpy(dest + strlen(dest), src);
  return dest;
}