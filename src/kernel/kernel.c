/**
 * @file kernel.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.5
 * @date 2021-07-06
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <drivers/keyboard/keyboard.h>
#include <drivers/video/video.h>
#include <drivers/vga/vga.h>
#include <kernel/syscalls/syscalls.h>
#include <kernel/devices/qemu.h>
#include <kernel/cpu/gdt/gdt.h>
#include <kernel/cpu/cpu.h>
#include <kernel/time/time.h>
#include <kernel/memory.h>
#include <kernel/kernel.h>
#include <kernel/stdio.h>
#include <kernel/errno.h>
#include <sys/utils.h>

void input()
{
    char ch = 0;
    char keycode = 0;
    do
    {
        keycode = get_input_keycode();
        if (keycode == KEY_ENTER)
        {
            vga_putchar('\n');
        }
        else
        {
            ch = get_ascii_char(keycode);
            vga_putchar(ch);
        }
        sleep(0x03FFFFFF);
    } while (ch > 0);
}

bool readKey(char key)
{
    char keycode = 0;
    do
    {
        keycode = get_input_keycode();
    } while (keycode != key);
    return true;
}

typedef void (*constructor)();
extern constructor *start_ctors;
extern constructor *end_ctors;
extern void call_constructors()
{
    for (constructor *i = start_ctors;
         i != end_ctors;
         i++)
    {
        (*i)();
    }
}

void kernel_entry()
{
    qemu_info("Kernel Initializing\r\n");
    qemu_info("Version: %s\r\n", KERNEL_VERSION);

    // Initialise the kernel since interupts are not enabled
    bool gdt = gdt_init();
    bool vga = vga_init();

    time_init();
    heap_init(0x100000, 0x100000);

    disable_cursor();
    clear_screen();

    qemu_success("Kernel Initialization Complete\r\n");

    kprintf("TinyKernel - %s\n", KERNEL_VERSION);
    kprintf(" [i] Kernel Version:   %s\n", KERNEL_VERSION);
    kprintf(" [i] Keyboard Driver:  Enabled\n");
    if (gdt == true)
    {
        kprintf(" [i] GDT:              Enabled\n");
        qemu_success("GDT Initialized: %x\r\n", gdt);
    }
    if (vga == true)
    {
        kprintf(" [i] VGA Driver:       Enabled\n");
        qemu_success("VGA Initialized: %x\r\n", vga);
    }

    cpuid_info();

    void* kmalloc_test = kmalloc(0x10);
    void* kmalloc_test1 = kmalloc(0x10);
    void* kmalloc_test2 = kmalloc(0x10);
    qemu_dbg("kmalloc_test: %x\r\n", kmalloc_test);
    qemu_dbg("kmalloc_test1: %x\r\n", kmalloc_test1);
    qemu_dbg("kmalloc_test2: %x\r\n", kmalloc_test2);
    vga_write_string("Heap Allocation Test:     --------", 35, 0);
    vga_write_string("[0] kmalloc: 0x10 -> 0x", 40, 1); vga_write_string(convert_to_base((uint64_t)kmalloc_test, 16), 63, 1);
    vga_write_string("[1] kmalloc: 0x10 -> 0x", 40, 2); vga_write_string(convert_to_base((uint64_t)kmalloc_test1, 16), 63, 2);
    vga_write_string("[2] kmalloc: 0x10 -> 0x", 40, 3); vga_write_string(convert_to_base((uint64_t)kmalloc_test2, 16), 63, 3);

    qemu_dbg("free\r\n");
    kfree(kmalloc_test);
    kfree(kmalloc_test1);
    kfree(kmalloc_test2);
    qemu_dbg("kmalloc_test: %x\r\n", kmalloc_test);
    qemu_dbg("kmalloc_test1: %x\r\n", kmalloc_test1);
    qemu_dbg("kmalloc_test2: %x\r\n", kmalloc_test2);

    void* kmalloc_test3 = kmalloc(0x10);
    void* kmalloc_test4 = kmalloc(0x10);
    void* kmalloc_test5 = kmalloc(0x10);
    qemu_dbg("kmalloc_test3: %x\r\n", kmalloc_test3);
    qemu_dbg("kmalloc_test4: %x\r\n", kmalloc_test4);
    qemu_dbg("kmalloc_test5: %x\r\n", kmalloc_test5);
    vga_write_string("Heap Free Test:           --------", 35, 4);
    vga_write_string("[3] kmalloc: 0x10 -> 0x", 40, 5); vga_write_string(convert_to_base((uint64_t)kmalloc_test3, 16), 63, 5);
    vga_write_string("[4] kmalloc: 0x10 -> 0x", 40, 6); vga_write_string(convert_to_base((uint64_t)kmalloc_test4, 16), 63, 6);
    vga_write_string("[5] kmalloc: 0x10 -> 0x", 40, 7); vga_write_string(convert_to_base((uint64_t)kmalloc_test5, 16), 63, 7);

    kprintf("\nPress enter to shut down\n");
    while (true)
    {
        if (readKey(KEY_ENTER) == true)
        {
            qemu_info("Shutting Down\r\n");
            sys_shutdown();
        }
    }

    sti();
}
