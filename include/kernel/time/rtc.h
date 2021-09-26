#ifndef RTC_H
#define RTC_H
#include <types.h>
#include <system.h>

#define CMOS_ADDR 0x70
#define CMOS_DATA 0x71

typedef struct datetime
{
    uint8_t century;
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} datetime_t;

int rtc_is_updating();
uint8_t rtc_get_register(uint8_t reg);
void rtc_set_register(uint8_t reg, uint8_t val);
void rtc_read_datetime();
void rtc_write_datetime(datetime_t *dt);
char *rtc_datetime_string(datetime_t *dt);
char *rtc_current_datetime_string();
int rtc_weekday_from_date(datetime_t *dt);
int rtc_leap_year(int year, int month);
void rtc_init();

#endif /* RTC_H */