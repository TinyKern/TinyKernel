#ifndef CPU_H
#define CPU_H

#include <types.h>

extern void cpuid(uint32 value, uint32 *eax, uint32 *ebx, uint32 *ecx, uint32 *edx);
extern void cpuid_test();

#endif // CPU_H