/**
 * @file kprintf.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.3
 * @date 2021-08-11
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <AK/printfImpl.h>

int __kprintf(char *fmt, ...)
{
    fmt += '\0';
    va_list args;
    va_start(args, fmt);
    int ret = printf_internal(fmt, args);
    va_end(args);
    return ret;
}
