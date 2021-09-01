/**
 * @file mktime.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.2
 * @date 2021-08-19
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */


#include <kernel/time/time.h>

#define MINUTE 60
#define HOUR (60 * MINUTE)
#define DAY (24 * HOUR)
#define YEAR (365 * DAY)

static int monthk[12] = {
    0,
    DAY * (31),
    DAY * (31+29),
    DAY * (31+29+31),
    DAY * (31+29+31+30),
    DAY * (31+29+31+30+31),
    DAY * (31+29+31+30+31+30),
    DAY * (31+29+31+30+31+30+31),
    DAY * (31+29+31+30+31+30+31+31),
    DAY * (31+29+31+30+31+30+31+31+30),
    DAY * (31+29+31+30+31+30+31+31+30+31),
    DAY * (31+29+31+30+31+30+31+31+30+31+30)
};

long time_init(void)
{
    struct tm time;

    do {
        time.tm_sec = READ_CMOS(0);
        time.tm_min = READ_CMOS(2);
        time.tm_hour = READ_CMOS(4);
        time.tm_mday = READ_CMOS(7);
        time.tm_mon = READ_CMOS(8) - 1;
        time.tm_year = READ_CMOS(9);
    } while (time.tm_sec != READ_CMOS(0));

    BCD_TO_BIN(time.tm_sec);
    BCD_TO_BIN(time.tm_min);
    BCD_TO_BIN(time.tm_hour);
    BCD_TO_BIN(time.tm_mday);
    BCD_TO_BIN(time.tm_mon);
    BCD_TO_BIN(time.tm_year);

    return mktime(&time);
}

long mktime(struct tm *tm)
{
    long res;
    int year;

    year = tm->tm_year - 70;

    res = YEAR*year + DAY*((year+1)/4);
    res += monthk[tm->tm_mon];

    if (tm->tm_mon > 1 && ((year+2) % 4))
        res -= DAY;
    
    res += DAY * (tm->tm_mday - 1);
    res += HOUR * tm->tm_hour;
    res += MINUTE * tm->tm_min;
    res += tm->tm_sec;
    return res;
}