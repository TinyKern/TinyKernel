#include <kernel/cpu/bios/cmos.h>
#include <kernel/cpu/cpu.h>

uint8 cmod_lowmem()
{
    uint8 lowmem;

    // Get the low memory size from CMOS
    outb(0x70, 0x30);
    lowmem = inb(0x71);
    return lowmem;
}

uint8 cmod_highmem()
{
    uint8 highmem;

    // Get the high memory size from CMOS
    outb(0x70, 0x31);
    highmem = inb(0x71);
    return highmem;
}

uint16 cmod_totalmem()
{
    uint16 totalmem;
    uint8 lowmem, highmem;

    lowmem = cmod_lowmem();
    highmem = cmod_highmem();

    // Calculate the total memory size
    totalmem = lowmem | highmem << 8;
    return totalmem;
}
