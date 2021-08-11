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

enum ERR_CODES
{
    ERRNO_KERNEL_INVALID_MAGIC      = 0x01,
    ERRNO_KERNEL_INVALID_SYSCALL    = 0x64,
    ERRNO_KERN_INVALID_ADDR,
    ERRNO_NO_FREE_PAGE_FRAME,
    ERRNO_KERNEL_KILL_PROCESS,
    ERRNO_NO_FREE_MEMORY            = 0xA3,
    ERRNO_MEMORY_HEAP_LIMIT         = 0xA4,
    ERRNO_NO_AVAILABLE_PAGE,
    ERRNO_FAILED_SHUTDOWN,
};

extern void     kprint_error(char*, char*);
extern int      kpanic(int errcode, char* errmsg, int hlt);

#endif
