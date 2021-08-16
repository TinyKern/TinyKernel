/**
 * @file cmos.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.0
 * @date 2021-08-15
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef CMOS_C
#define CMOS_C

#include <types.h>

extern uint8 cmod_lowmem();
extern uint8 cmod_highmem();
extern uint16 cmod_totalmem();

#endif // CMOS_C