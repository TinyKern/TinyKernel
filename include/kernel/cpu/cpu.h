#ifndef CPU_H
#define CPU_H

#include <types.h>
#include "ports.h"

#define LSW(x) ((uint32)(x)&0xFFFF)
#define MSW(x) (((uint32)(x) >> 16) & 0xFFFF)
#define LSB(x) ((x)&0xFF)
#define MSB(x) (((x) >> 8) & 0xFF)

extern void cpuid(uint32 value, uint32 *eax, uint32 *ebx, uint32 *ecx, uint32 *edx);
extern void cpuid_info();

#endif // CPU_H