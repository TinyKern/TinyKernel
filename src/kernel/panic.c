/**
 * @file panic.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.4
 * @date 2021-08-24
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <config.h>

#include <kernel/panic.h>
#include <debug/qemu.h>

#include <arch/i386/elf_core.h>
#include <arch/i386/paging.h>

volatile bool __in_panic;
volatile bool __in_double_fault;
volatile bool __in_kernel_shutdown;

void kpanic(int errcode, char* errmsg)
{
    clear_screen();
    vga_set_default_color(vga_create_color(BLACK, WHITE));
    kprintf("Kernel panic: %s - 0x%x\n", errmsg, errcode);
    qemu_panic("Kernel panic: %s - %x\n", errmsg, errcode);
    for(;;) {}
}
