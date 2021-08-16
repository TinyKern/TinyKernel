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

uint32 strlen(const char *str)
{
  uint32 length = 0;
  while (str[length])
    length++;
  return length;
}

int strcmp(const char *s1, const char *s2)
{
  while (*s1 == *s2++)
    if (*s1++ == 0)
      return 0;
  return (*(uint8*)s1 - *(uint8*)--s2);
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