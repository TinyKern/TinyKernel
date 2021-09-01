/**
 * @file tty.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.0.7
 * @date 2021-08-24
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef TTY_H
#define TTY_H

#include <types.h>

struct tty;

static ALWAYS_INLINE struct tty *get_curr_tty(void)
{
    extern struct tty *__curr_tty;
    return __curr_tty;
}

#endif // TTY_H