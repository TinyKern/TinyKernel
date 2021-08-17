/**
 * @file shutdown.c
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

#include <kernel/syscalls/shutdown.h>

void sys_shutdown(void)
{
  out16(0x604, 0x2000);
  out16(0x4004, 3400);
  out16(0xb004, 0x2000);
  kpanic(ERRNO_FAILED_SHUTDOWN, "Failed to shutdown", true);
}