/**
 * @file syscalls.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.2
 * @date 2021-07-06
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <kernel/cpu/cpu.h>
#include <kernel/errno.h>
#include <kernel/panic.h>
#include <cdefs.h>

/**
 * @brief Shutdown the system.
 */
extern void sys_shutdown(void);

#endif // SYSCALLS_H