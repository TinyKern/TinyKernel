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

#include "types.h"

extern uint16_t* vga_buffer;

// Index for video buffer array
extern uint32_t vga_index;

extern uint8_t g_fore_color;
extern uint8_t g_back_color;

#define KERNEL_VERSION "1.3.6"

#define INFO_COLORS     "[\033[1;36minfo\033[0m] "
#define DEBUG_COLORS    "[\033[0;33m\033[4mdebug\033[0m] "
#define SUCCESS_COLORS  "[\033[1;32msuccess\033[0m] "

#endif
