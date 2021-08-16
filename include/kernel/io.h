/**
 * @file boot.s
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.3
 * @date 2021-07-12
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef IO_H
#define IO_H

#include <types.h>

/**
 * keep the cpu busy for doing nothing(nop)
 * so that io port will not be processed by cpu
 * here timer can also be used, but lets do this in looping counter
 */
extern void wait_for_io(uint32 timer_count);

extern void sleep(uint32 timer_count);

#endif // IO_H