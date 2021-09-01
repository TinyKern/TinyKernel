/**
 * @file time.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.0
 * @date 2021-08-19
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef TIME_H
#define TIME_H

#include <kernel/cpu/bios/cmos.h>

struct tm
{
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};

#define BCD_TO_BIN(val) ((val) = ((val)&15) + ((val)>>4)*10)

extern long time_init(void);

extern long mktime(struct tm*);

#endif // TIME_H