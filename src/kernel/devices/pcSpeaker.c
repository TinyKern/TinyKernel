/**
 * @file pcSpeaker.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.1
 * @date 2021-08-13
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <kernel/devices/pcSpeaker.h>
#include <kernel/time/PIT.h>
#include <kernel/cpu/cpu.h>
#include <kernel/io.h>

void pcs_tone_on(uint32_t freq)
{
    uint32_t div;
    uint8_t tmp;

    // Set the PIT to the desired frequency
    div = BASE_FREQ / freq;
    outb(0x43, 0xb6);
    outb(0x42, (uint8_t)(div));
    outb(0x42, (uint8_t)(div >> 8));

    // Play sound using PC speaker
    tmp = inb(0x61);
    if (tmp != (tmp | 3))
        outb(0x61, tmp | 3);
}

void pcs_tone_off()
{
    uint8_t tmp = inb(0x61) & 0xFC;

    outb(0x61, tmp);
}

void pcs_beep()
{
    pcs_tone_on(1000);
    sleep(10000000);
    pcs_tone_off();
}