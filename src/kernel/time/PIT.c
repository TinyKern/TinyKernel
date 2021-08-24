#include <kernel/time/PIT.h>
#include <kernel/stdio.h>

unsigned read_pit_count(void)
{
    unsigned count = 0;

    // Disables interrupts
    cli();

    outb(0x43, 0b0000000);

    // Reads the count
    count = inb(0x40);          // Low byte
    count |= inb(0x40) << 8;    // High byte

    return count;
}

void set_pit_count(unsigned count)
{
    // Disables interrupts
    cli();

    // Set low byte
    outb(0x40, count & 0xFF);
    outb(0x40, (count & 0xFF00) >> 8);
    return;
}
