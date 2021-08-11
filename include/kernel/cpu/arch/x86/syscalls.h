#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <kernel/cpu/cpu.h>
#include <kernel/errno.h>
#include <types.h>

void sys_shutdown(void)
{
  out16(0x604, 0x2000);
  out16(0x4004, 3400);
  out16(0xb004, 0x2000);
  kpanic(ERRNO_FAILED_SHUTDOWN, "Failed to shutdown", TRUE);
}

#endif // SYSCALLS_H