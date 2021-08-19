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