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

#include <multiboot.h>
#include <drivers/keyboard/keyboard.h>
#include <drivers/video/video.h>
#include <drivers/vga/vga.h>
#include <kernel/syscalls/syscalls.h>
#include <kernel/devices/pcSpeaker.h>
#include <kernel/devices/qemu.h>
#include <kernel/cpu/gdt/gdt.h>
#include <kernel/cpu/cpu.h>
#include <kernel/time/time.h>
#include <kernel/time/PIT.h>
#include <kernel/memory.h>
#include <kernel/kernel.h>
#include <kernel/stdio.h>
#include <kernel/errno.h>
#include <sys/utils.h>
#include <cdefs.h>

void kernel_entry();

void input()
{
    char ch = 0;
    do
    {
        char keycode = get_input_keycode();
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

void loading_bar(int x, int y, int len, char* message, uint8_t color)
{
    int i = 0;

    set_buffer_position((x - (len / 2)), y - 1);
    kprintf(message);

    x -= (len / 2);
    for (i = 0; i < len; i++)
    {
        draw(x, y, color);
        sleep(15000000);
        x += 1;
    }
    sleep(200000000);
    clear_screen();
}

void kernel_entry(multiboot_info_t *mbi, uint32_t magic)
{

#ifdef QEMU_SERIAL_ENABLED
    qemu_info("Kernel Initializing\r\n");
    qemu_info("Version: %s\r\n", KERNEL_VERSION);
    qemu_info("Compiler: %s - %u\r\n", COMPILER_NAME, COMPILER_VERSION);
    qemu_info("Architecture: %s\r\n", __BUILD_ARCH__);
    qemu_info("Build: %s\r\n", __BUILD_DATE__);
    qemu_info("magic x: %x\n", magic);
    qemu_info("magic u: %u\n", magic);
    get_current_time();
#endif // QEMU_SERIAL_ENABLED


    // Initialise the kernel since interupts are not enabled
    bool gdt = gdt_init();
    bool vga = vga_init();

    if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
        kpanic(ERRNO_KERNEL_INVALID_MAGIC, "Invalid magic number");

    ASSERT(mbi->mods_count > 0);

#ifdef QEMU_SERIAL_ENABLED
    qemu_info("Multiboot flags: %x\n", mbi->flags);
    qemu_info("Multiboot mem_lower: %x\n", mbi->mem_lower);
    qemu_info("Multiboot mem_upper: %x\n", mbi->mem_upper);
    qemu_info("Multiboot boot_device: %x\n", mbi->boot_device);
    qemu_info("Multiboot cmdline: %x\n", mbi->cmdline);
    qemu_info("Multiboot mmap_length: %x\n", mbi->mmap_length);
    qemu_info("Multiboot mmap_addr: %x\n", mbi->mmap_addr);
#endif // QEMU_SERIAL_ENABLED

    time_init();
    heap_init(0x100000, 0x100000);


    disable_cursor();
    clear_screen();


    char* loading_message = "TinyKernel Booting";
    loading_bar(VGA_COLS / 2, VGA_ROWS / 2, strlen(loading_message), loading_message, 0xff);

#ifdef QEMU_SERIAL_ENABLED
    qemu_success("Kernel Initialization Complete\r\n");
#endif // QEMU_SERIAL_ENABLED

    kprintf("TinyKernel - %s\n", KERNEL_VERSION);
    kprintf(" [i] Kernel Version:   %s\n", KERNEL_VERSION);
    kprintf(" [i] Keyboard Driver:  Enabled\n");
    if (gdt == true)
    {
        kprintf(" [i] GDT:              Enabled\n");
#ifdef QEMU_SERIAL_ENABLED
        qemu_success("GDT Initialized: %x\r\n", gdt);
#endif // QEMU_SERIAL_ENABLED
    }
    if (vga == true)
    {
        kprintf(" [i] VGA Driver:       Enabled\n");
#ifdef QEMU_SERIAL_ENABLED
        qemu_success("VGA Initialized: %x\r\n", vga);
#endif // QEMU_SERIAL_ENABLED
    }

    cpuid_info();

    void* kmalloc_test = kmalloc(0x10);
    void* kmalloc_test1 = kmalloc(0x10);
    void* kmalloc_test2 = kmalloc(0x10);
#ifdef QEMU_SERIAL_ENABLED
    qemu_dbg("kmalloc_test: %x\r\n", kmalloc_test);
    qemu_dbg("kmalloc_test1: %x\r\n", kmalloc_test1);
    qemu_dbg("kmalloc_test2: %x\r\n", kmalloc_test2);
#endif // QEMU_SERIAL_ENABLED
    vga_write_string("Heap Allocation Test:     --------", 35, 0);
    vga_write_string("[0] kmalloc: 0x10 -> 0x", 40, 1); vga_write_string(convert_to_base((uint64_t)kmalloc_test, 16), 63, 1);
    vga_write_string("[1] kmalloc: 0x10 -> 0x", 40, 2); vga_write_string(convert_to_base((uint64_t)kmalloc_test1, 16), 63, 2);
    vga_write_string("[2] kmalloc: 0x10 -> 0x", 40, 3); vga_write_string(convert_to_base((uint64_t)kmalloc_test2, 16), 63, 3);

    qemu_dbg("free\r\n");
    kfree(kmalloc_test);
    kfree(kmalloc_test1);
    kfree(kmalloc_test2);
#ifdef QEMU_SERIAL_ENABLED
    qemu_dbg("kmalloc_test: %x\r\n", kmalloc_test);
    qemu_dbg("kmalloc_test1: %x\r\n", kmalloc_test1);
    qemu_dbg("kmalloc_test2: %x\r\n", kmalloc_test2);
#endif // QEMU_SERIAL_ENABLED

    void* kmalloc_test3 = kmalloc(0x10);
    void* kmalloc_test4 = kmalloc(0x10);
    void* kmalloc_test5 = kmalloc(0x10);
#ifdef QEMU_SERIAL_ENABLED
    qemu_dbg("kmalloc_test3: %x\r\n", kmalloc_test3);
    qemu_dbg("kmalloc_test4: %x\r\n", kmalloc_test4);
    qemu_dbg("kmalloc_test5: %x\r\n", kmalloc_test5);
#endif // QEMU_SERIAL_ENABLED
    vga_write_string("Heap Free Test:           --------", 35, 4);
    vga_write_string("[3] kmalloc: 0x10 -> 0x", 40, 5); vga_write_string(convert_to_base((uint64_t)kmalloc_test3, 16), 63, 5);
    vga_write_string("[4] kmalloc: 0x10 -> 0x", 40, 6); vga_write_string(convert_to_base((uint64_t)kmalloc_test4, 16), 63, 6);
    vga_write_string("[5] kmalloc: 0x10 -> 0x", 40, 7); vga_write_string(convert_to_base((uint64_t)kmalloc_test5, 16), 63, 7);

    kprintf("\nPress enter to shut down\n");
    while (true)
    {
        if (readKey(KEY_ENTER) == true)
        {
#ifdef QEMU_SERIAL_ENABLED
            qemu_success("Shutting Down\r\n");
#endif // QEMU_SERIAL_ENABLED
            sys_shutdown();
        }
    }

    sti();
}
