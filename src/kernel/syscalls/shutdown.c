#include <kernel/syscalls/shutdown.h>

void sys_shutdown(void)
{
  out16(0x604, 0x2000);
  out16(0x4004, 3400);
  out16(0xb004, 0x2000);
  kpanic(ERRNO_FAILED_SHUTDOWN, "Failed to shutdown", TRUE);
}