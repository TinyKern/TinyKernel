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

#include "buildinfo.h"
#include "types.h"

extern uint16_t* vga_buffer;

// Index for video buffer array
extern uint32_t vga_index;

extern uint8_t g_fore_color;
extern uint8_t g_back_color;

#define KERNEL_VERSION __BUILD_VERSION__

#ifdef __clang__
# define COMPILER_VERSION    __clang_version__
# define COMPILER_NAME       "clang"
#elif __GNUC__
# define COMPILER_VERSION    __GNUC__
# define COMPILER_NAME       "gcc"
#else
# define COMPILER_VERSION    "unknown"
# define COMPILER_NAME       "unknown"
#endif

#define INFO_COLORS     "[\033[1;36minfo\033[0m]    "
#define DEBUG_COLORS    "[\033[0;33m\033[4mdebug\033[0m]   "
#define SUCCESS_COLORS  "[\033[1;32msuccess\033[0m] "
#define ERROR_COLORS    "[\033[1;31merror\033[0m] %u, %s | "
#define PANIC_COLORS    "[\033[1;31mpanic\033[0m]   "

#define KB (1024u)
#define MB (1024u*KB)

#define USE_ELF32
#define KERNEL_SYMBOLS 1

#define KERNEL_BASE_VA  0xC0000000
#define KERNEL_PADDR    0x00100000

#define QEMU_SERIAL_ENABLED

#define CURRENT_YEAR    2021

#endif
