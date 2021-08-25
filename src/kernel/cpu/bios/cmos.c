/**
 * @file cmos.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.0
 * @date 2021-08-15
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <config.h>

#include <kernel/cpu/bios/cmos.h>
#include <kernel/devices/qemu.h>
#include <kernel/cpu/cpu.h>

uint8_t cmod_lowmem()
{
    uint8_t lowmem;

    // Get the low memory size from CMOS
    outb(0x70, 0x30);
    lowmem = inb(0x71);
    return lowmem;
}

uint8_t cmod_highmem()
{
    uint8_t highmem;

    // Get the high memory size from CMOS
    outb(0x70, 0x31);
    highmem = inb(0x71);
    return highmem;
}

uint16_t cmod_totalmem()
{
    uint16_t totalmem;
    uint8_t lowmem, highmem;

    lowmem = cmod_lowmem();
    highmem = cmod_highmem();

    // Calculate the total memory size
    totalmem = lowmem | highmem << 8;
    return totalmem;
}

uint8_t  second;
uint8_t  minute;
uint8_t  hour;
uint8_t  day;
uint8_t  month;
uint32_t year;
uint8_t  century;
uint8_t  last_second;
uint8_t  last_minute;
uint8_t  last_hour;
uint8_t  last_day;
uint8_t  last_month;
uint8_t  last_year;
uint8_t  last_century;
uint8_t  registerB;

int century_register = 0x00;

enum
{
    cmos_address    = 0x70,
    cmos_data       = 0x71
};

int get_update_in_progress_flag() {
      outb(cmos_address, 0x0A);
      return (inb(cmos_data) & 0x80);
}


uint8_t get_rtc_register(int reg) {
      outb(cmos_address, reg);
      return inb(cmos_data);
}

void read_rtc()
{
    /* Note:    This uses the "read registers until you
                get the same values in a row" technique
                to avoid getting inconsistent values due to RTC updates
    */

    // Make sure that an update isn't in progress
    while (get_update_in_progress_flag());

    second   = get_rtc_register(0x00);
    minute   = get_rtc_register(0x02);
    hour     = get_rtc_register(0x04);
    day      = get_rtc_register(0x07);
    month    = get_rtc_register(0x08);
    year     = get_rtc_register(0x09);

    if (century_register != 0)
        century = get_rtc_register(century_register);

    do
    {
        last_second   = second;
        last_minute   = minute;
        last_hour     = hour;
        last_day      = day;
        last_month    = month;
        last_year     = year;
        last_century  = century;

        while (get_update_in_progress_flag());  // Wait for update to finish

        second   = get_rtc_register(0x00);
        minute   = get_rtc_register(0x02);
        hour     = get_rtc_register(0x04);
        day      = get_rtc_register(0x07);
        month    = get_rtc_register(0x08);
        year     = get_rtc_register(0x09);

        if (century_register != 0)
            century = get_rtc_register(century_register);
    } while(
        (last_second   != second)   ||
        (last_minute   != minute)   ||
        (last_hour     != hour)     ||
        (last_day      != day)      ||
        (last_month    != month)    ||
        (last_year     != year)     ||
        (last_century  != century)
    );

    registerB = get_rtc_register(0x0B);

    // Convert BCD to binary values if necessary
    if (!(registerB & 0x04))
    {
        second  = (second & 0x0F) + ((second / 16) * 10);
        minute  = (minute & 0x0F) + ((minute / 16) * 10);
        hour    = ((hour & 0x0F) + (((hour & 0x70) / 16) * 10)) | (hour & 0x80);
        day     = (day & 0x0F) + ((day / 16) * 10);
        month   = (month & 0x0F) + ((month / 16) * 10);
        year    = (year & 0x0F) + ((year / 16) * 10);

        if (century_register != 0)
            century = (century & 0x0F) + ((century / 16) * 10);
    }

    // Convert 12 hour clock to 24 hour clock if necessary
    if (!(registerB & 0x02) && (hour & 0x80))
        hour = ((hour & 0x7F) + 12) % 24;

    // Calculate the full (4-digit) year
    if (century_register != 0)
        year += century * 100;
    else
    {
        year += (CURRENT_YEAR / 100) * 100;
        if (year < CURRENT_YEAR) year += 100;
    }
}

// FIXME: This is a hack to get around the fact that QEMU doesn't support the CMOS registers 0x0B and 0x0C
void get_current_time()
{
    read_rtc();
#ifdef QEMU_SERIAL_ENABLED
    qemu_info("time: %u.%u.%u %u:%u\n", day, month, year, hour, minute);
#endif
}