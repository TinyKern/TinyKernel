/**
 * @file errno.h
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

#ifndef ERRNO_H
#define ERRNO_H

// Syscall error codes
#define ENOSYS      38  // Invalid system call number

#define EINTR       4   // Interrupted system call
#define EIO         5   // I/O error
#define ENXIO       6   // No such device or address
#define E2BIG       7   // Argument list too long
#define ENOEXEC     8   // Exec format error

#define ESHUTD      87  // Failed to send shutdown signal

enum ERR_CODES
{
    ERRNO_KERNEL_INVALID_MAGIC      = 0x01, //!< Invalid magic number
    ERRNO_KERNEL_INVALID_SYSCALL    = 0x64, //!< Invalid syscall
    ERRNO_KERN_INVALID_ADDR,                //!< Invalid address
    ERRNO_NO_FREE_PAGE_FRAME,               //!< No free page frame available
    ERRNO_KERNEL_KILL_PROCESS,              //!< Process killed
    ERRNO_NO_FREE_MEMORY            = 0xA3, //!< No free memory available
    ERRNO_MEMORY_HEAP_LIMIT         = 0xA4, //!< Memory heap limit reached
    ERRNO_NO_AVAILABLE_PAGE,                //!< No available page
};

#endif
