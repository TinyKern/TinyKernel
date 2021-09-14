/**
 * @file errno.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.2
 * @date 2021-07-09
 *
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef ERRNO_H
#define ERRNO_H

#define EFAULT 14

// Syscall error codes
#define ENOSYS      38  // Invalid system call number

#define EINTR       4   // Interrupted system call
#define EIO         5   // I/O error
#define ENXIO       6   // No such device or address
#define E2BIG       7   // Argument list too long
#define ENOEXEC     8   // Exec format error

#define ESHUTD      87  // Failed to send shutdown signal

/**
 * 0        - Division by zero exception
 * 1        - Debug exception
 * 2        - Non maskable interrupt
 * 3        - Breakpoint exception
 * 4        - 'Into detected overflow'
 * 5        - Out of bounds exception
 * 6        - Invalid opcode exception
 * 7        - No coprocessor exception
 * 8        - Double fault (pushes an error code)
 * 9        - Coprocessor segment overrun
 * 10       - Bad TSS (pushes an error code)
 * 11       - Segment not present (pushes an error code)
 * 12       - Stack fault (pushes an error code)
 * 13       - General protection fault (pushes an error code)
 * 14       - Page fault (pushes an error code)
 * 15       - Unknown interrupt exception
 * 16       - Coprocessor fault
 * 17       - Alignment check exception
 * 18       - Machine check exception
 * 19-32    - Reserved
 */
enum interrupt_exception
{
    EXCEPTION_DIVISION_BY_ZERO = 0,
    EXCEPTION_DEBUG = 1,
    EXCEPTION_NMI = 2,
    EXCEPTION_BREAKPOINT = 3,
    EXCEPTION_OVERFLOW = 4,
    EXCEPTION_BOUNDS = 5,
    EXCEPTION_INVALID_OPCODE = 6,
    EXCEPTION_NO_COPROCESSOR = 7,
    EXCEPTION_DOUBLE_FAULT = 8,
    EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN = 9,
    EXCEPTION_BAD_TSS = 10,
    EXCEPTION_SEGMENT_NOT_PRESENT = 11,
    EXCEPTION_STACK_FAULT = 12,
    EXCEPTION_GENERAL_PROTECTION_FAULT = 13,
    EXCEPTION_PAGE_FAULT = 14,
    EXCEPTION_UNKNOWN_INTERRUPT = 15,
    EXCEPTION_COPROCESSOR_FAULT = 16,
    EXCEPTION_ALIGNMENT_CHECK = 17,
    EXCEPTION_MACHINE_CHECK = 18,
    EXCEPTION_RESERVED_19 = 19,
    EXCEPTION_RESERVED_20, EXCEPTION_RESERVED_21, EXCEPTION_RESERVED_22,
    EXCEPTION_RESERVED_23, EXCEPTION_RESERVED_24, EXCEPTION_RESERVED_25,
    EXCEPTION_RESERVED_26, EXCEPTION_RESERVED_27, EXCEPTION_RESERVED_28,
    EXCEPTION_RESERVED_29, EXCEPTION_RESERVED_30, EXCEPTION_RESERVED_31,
    EXCEPTION_RESERVED_32,
};

enum ERR_CODES
{
    ERRNO_KERNEL_INVALID_MAGIC      = 0x01, //!< Invalid magic number
    ERRNO_KERNEL_INVALID_FLAGS,             //!< Invalid flags
    ERRNO_KERNEL_INVALID_SYSCALL    = 0x64, //!< Invalid syscall
    ERRNO_KERN_INVALID_ADDR,                //!< Invalid address
    ERRNO_NO_FREE_PAGE_FRAME,               //!< No free page frame available
    ERRNO_KERNEL_KILL_PROCESS,              //!< Process killed
    ERRNO_NO_FREE_MEMORY            = 0xA3, //!< No free memory available
    ERRNO_MEMORY_HEAP_LIMIT         = 0xA4, //!< Memory heap limit reached
    ERRNO_NO_AVAILABLE_PAGE,                //!< No available page
};

#endif
