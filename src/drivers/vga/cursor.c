#include <drivers/vga/cursor.h>
#include <kernel/cpu/cpu.h>

void enable_cursor(uint8_t start, uint8_t end)
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | start);

    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | end);
}