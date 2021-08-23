#ifndef QEMU_H
#define QEMU_H

#include <config.h>

#include <kernel/cpu/ports.h>
#include <stdarg.h>
#include <types.h>

void qemu_puthex(uint32_t i);
void qemu_printf(char* fmt, ...);

void qemu_dbg(char *fmt, ...);
void qemu_success(char *fmt, ...);
void qemu_info(char *fmt, ...);

#endif // QEMU_H