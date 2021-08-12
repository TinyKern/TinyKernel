#include <kernel/devices/pcSpeaker.h>
#include <kernel/time/PIT.h>
#include <kernel/cpu/cpu.h>

void tone_on(int freq)
{
    // out8(PIT_CTL, TIMER_T2_SELECT | WRITE_WORD | MODE_SQAURE_WAVE);
    // uint16 timer_reload = BASE_FREQ / freq;

    // out8(TIMER_T2_CTL, LSB(timer_reload));
    // out8(TIMER_T2_CTL, MSB(timer_reload));

    // out8(0x61, in8(0x61) | 3);

    int scale;
    if (freq == 0)
    {
        outb(0x61, inb(0x61) & ~3);
        return;
    }

    scale = (int)(BASE_FREQ / freq);
    outb(0x43, 0xb6);
    outb(0x42, scale & 0xff);
    outb(0x42, scale >> 8);
    outb(0x61, inb(0x61) | 3);
}

void tone_off()
{
    out8(0x61, in8(0x61) & ~3);
}