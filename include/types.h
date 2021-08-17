/**
 * @file types.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.3
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef TYPES_H
#define TYPES_H

#include <sys/stddef.h>

// Unsigned types
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

// Signed types
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long int64_t;

// float types
typedef float float32_t;
typedef double float64_t;

// aliases
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef float32_t f32;
typedef float64_t f64;

// unsigned pointers
typedef unsigned long int uintptr_t;

#define NULLPTR NULL

typedef enum {false, true} bool;

#endif
