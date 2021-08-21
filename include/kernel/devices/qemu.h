#ifndef QEMU_H
#define QEMU_H

#include <kernel/cpu/ports.h>
#include <stdarg.h>
#include <types.h>

void qemu_puthex(uint32_t i);
void qemu_printf(char* fmt, ...);

#define qemu_debug(fmt, ...) qemu_printf(fmt, ##__VA_ARGS__)

#endif // QEMU_H