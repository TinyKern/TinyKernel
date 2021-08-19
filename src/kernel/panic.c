#include <kernel/panic.h>

void kpanic(int errcode, char* errmsg)
{
    clear_screen();
    vga_set_default_color(vga_create_color(BLACK, WHITE));
    kprintf("Kernel panic: %s - 0x%x", errmsg, errcode);
    for(;;) {}
}
