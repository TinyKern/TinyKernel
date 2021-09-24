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

long mktime(struct tm *tm)
{
    long res;
    int year;

    year = tm->tm_year - 70;
    /* Magic offset (y+1) to get leap year */
    res = YEAR*year + DAY*((year+1)/4);
    res += monthk[tm->tm_mon];
    /* Magic offset (y+2) to get non-leap year */
    if (tm->tm_mon > 1 && ((year+2) % 4))
        res -= DAY;
    res += DAY * (tm->tm_mday - 1);
    res += HOUR * tm->tm_hour;
    res += MINUTE * tm->tm_min;
    res += tm->tm_sec;
    return res;
}