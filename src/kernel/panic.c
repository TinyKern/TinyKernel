#include <config.h>

#include <kernel/devices/qemu.h>
#include <kernel/panic.h>

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

#ifdef QEMU_SERIAL_ENABLED
    qemu_panic("Kernel panic: %s - %x\n", errmsg, errcode);
#endif // QEMU_SERIAL_ENABLED

    for(;;) {}
}
