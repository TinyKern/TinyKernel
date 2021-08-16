/**
 * @file shutdown.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.1
 * @date 2021-08-12
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef SYS_SHUTDOWN_H
#define SYS_SHUTDOWN_H

#include <kernel/cpu/cpu.h>
#include <kernel/errno.h>
#include <types.h>

extern void sys_shutdown(void);

#endif // SYS_SHUTDOWN_H