/**
 * @file configure.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.1
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <sys/types.h>

extern uint16* vga_buffer;

// Index for video buffer array
extern uint32 vga_index;

extern uint8 g_fore_color;
extern uint8 g_back_color;

#endif
