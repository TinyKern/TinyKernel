#include <kernel/devices/pcSpeaker.h>
#include <kernel/time/PIT.h>
#include <kernel/cpu/cpu.h>
#include <kernel/io.h>

void pcs_tone_on(uint32 freq)
{
    uint32 div;
    uint8 tmp;

    // Set the PIT to the desired frequency
    div = BASE_FREQ / freq;
    outb(0x43, 0xb6);
    outb(0x42, (uint8)(div));
    outb(0x42, (uint8)(div >> 8));

    // Play sound using PC speaker
    tmp = inb(0x61);
    if (tmp != (tmp | 3))
        outb(0x61, tmp | 3);
}

void pcs_tone_off()
{
    uint8 tmp = inb(0x61) & 0xFC;

    outb(0x61, tmp);
}

void pcs_beep()
{
    pcs_tone_on(1000);
    wait_for_io(1000);
    pcs_tone_off();
}