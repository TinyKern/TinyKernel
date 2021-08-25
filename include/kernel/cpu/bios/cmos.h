/**
 * @file cmos.h
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

#ifndef CMOS_C
#define CMOS_C

#include <types.h>
#include <kernel/cpu/cpu.h>

#define READ_CMOS(addr) ({ \
    outb_p(0x80 | addr, 0x70); \
    inb_p(0x71); \
})

extern uint8_t cmod_lowmem();
extern uint8_t cmod_highmem();
extern uint16_t cmod_totalmem();

extern uint8_t  second;
extern uint8_t  minute;
extern uint8_t  hour;
extern uint8_t  day;
extern uint8_t  month;
extern uint32_t year;
extern uint8_t  century;
extern uint8_t  last_second;
extern uint8_t  last_minute;
extern uint8_t  last_hour;
extern uint8_t  last_day;
extern uint8_t  last_month;
extern uint8_t  last_year;
extern uint8_t  last_century;
extern uint8_t  registerB;

void read_rtc();

void get_current_time();

#endif // CMOS_C