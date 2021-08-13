#include <kernel/devices/pcSpeaker.h>
#include <kernel/syscalls/beep.h>
#include <kernel/errno.h>
// #include <kernel/thread.h>
#include <kernel/io.h>
#include <kernel/time/PIT.h>

int sys_beep(int freq)
{
    // tone_on(440);
    // // auto result = sleep(1000);
    // sleep(1000);
    // // tone_off();
    // // if (result == -1)
    // //     return EINTR;
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
    return 0;
}