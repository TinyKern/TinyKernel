/**
 * @file types.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.5
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
#include "cdefs.h"

// Byte
typedef unsigned char       byte;
typedef signed char         sbyte;

// Unsigned types
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long       uint64_t;
typedef unsigned long long  uint128_t;

// Signed types
typedef signed char         int8_t;
typedef signed short        int16_t;
typedef signed int          int32_t;
typedef signed long         int64_t;
typedef signed long long    int128_t;

// Words
typedef short               word_t;
typedef int                 dword_t;
typedef long                qword_t;

typedef short               word;
typedef int                 dword;
typedef long                qword;


// float types
typedef float       float_t;
typedef float       float32_t;
typedef double      float64_t;
typedef long double float128_t;

// aliases
typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;
typedef int8_t      s8;
typedef int16_t     s16;
typedef int32_t     s32;
typedef int64_t     s64;
typedef float32_t   f32;
typedef float64_t   f64;
typedef float128_t  f128;

// unsigned pointers
typedef unsigned long int uintptr_t;
typedef unsigned long int uintptr;

#define NULLPTR NULL

// Pointer types
typedef char        *string;
typedef void        *voidptr;
typedef int         *intptr;
typedef uint8_t     *uint8ptr;
typedef uint16_t    *uint16ptr;
typedef uint32_t    *uint32ptr;
typedef uint64_t    *uint64ptr;
typedef int8_t      *int8ptr;
typedef int16_t     *int16ptr;
typedef int32_t     *int32ptr;
typedef int64_t     *int64ptr;
typedef float32_t   *float32ptr;
typedef float64_t   *float64ptr;
typedef float128_t  *float128ptr;

/* Boolean */
typedef enum {false=0, true} bool;
#define FALSE   false
#define TRUE    true

/* Registers - interrupt/exception */
typedef struct Registers
{
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} register_t;

/* Registers - Bios service */
typedef struct Register16
{
    uint16_t di, si, bp, sp, bx, dx, cx, ax;
    uint16_t ds, es, fs, gs, ss;
    uint16_t eflags;
} register16_t;

#define ALWAYS_INLINE __attribute__((always_inline))
#define NO_RETURN __attribute__((noreturn))
#define UNUSED __attribute__((unused))
#define PACKED __attribute__((packed))
#define ALIGNED(x) __attribute__((aligned(x)))
#define ALIGNED_STRUCT(x) __attribute__((aligned(x))) struct
#define ALIGNED_UNION(x) __attribute__((aligned(x))) union
#define ALIGNED_TYPEDEF(x) __attribute__((aligned(x))) typedef
#define ALIGNED_ENUM(x) __attribute__((aligned(x))) enum
#define DEPRECATED __attribute__((deprecated))

#define __always_inline inline __attribute__((always_inline))
#define __no_return __attribute__((noreturn))
#define __unused __attribute__((unused))
#define __packed __attribute__((packed))
#define __aligned(x) __attribute__((aligned(x)))
#define __aligned_struct(x) __attribute__((aligned(x))) struct
#define __aligned_union(x) __attribute__((aligned(x))) union
#define __aligned_typedef(x) __attribute__((aligned(x))) typedef
#define __aligned_enum(x) __attribute__((aligned(x))) enum
#define __deprecated __attribute__((deprecated))

#endif
