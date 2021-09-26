#include <kernel/time/rtc.h>
#include <kernel/cpu/cpu.h>
#include <kernel/memory.h>
#include <sys/string.h>
#include <sys/utils.h>

/* Global date time variable */
datetime_t current_datetime;

char *weekday_map[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

/**
 * @brief Check if the RTC is updating the time
 */
int rtc_is_updating()
{
    outb(CMOS_ADDR, 0x0A);
    uint32_t status = inb(CMOS_DATA);
    return (status & 0x80);
}

/**
 * @brief Get the value of a specific rtc register
 * 
 * @param reg 
 * @return uint8_t 
 */
uint8_t rtc_get_register(uint8_t reg)
{
    outb(CMOS_ADDR, reg);
    return inb(CMOS_DATA);
}

/**
 * @brief Set the value of a specific rtc register
 * 
 * @param reg 
 * @param val 
 */
void rtc_set_register(uint8_t reg, uint8_t val)
{
    outb(CMOS_ADDR, reg);
    outb(CMOS_DATA, val);
}


/**
 * @brief Read the current time from the RTC, and update the global variable
 */
void rtc_read_datetime()
{
    /* Wait for the RTC to be updated */
    while (rtc_is_updating());

    current_datetime.second = rtc_get_register(0x00);
    current_datetime.minute = rtc_get_register(0x02);
    current_datetime.hour = rtc_get_register(0x04);
    current_datetime.day = rtc_get_register(0x07);
    current_datetime.month = rtc_get_register(0x08);
    current_datetime.year = rtc_get_register(0x09);

    uint8_t register_b = rtc_get_register(0x0B);

    /* Convert BCD to binary values if necessary */
    if (!(register_b & 0x04))
    {
        current_datetime.second = (current_datetime.second & 0x0F) + ((current_datetime.second / 16) * 10);
        current_datetime.minute = (current_datetime.minute & 0x0F) + ((current_datetime.minute / 16) * 10);
        current_datetime.hour = ( (current_datetime.hour & 0x0F) + (((current_datetime.hour & 0x70) / 16) * 10) ) | (current_datetime.hour & 0x80);
        current_datetime.day = (current_datetime.day & 0x0F) + ((current_datetime.day / 16) * 10);
        current_datetime.month = (current_datetime.month & 0x0F) + ((current_datetime.month / 16) * 10);
        current_datetime.year = (current_datetime.year & 0x0F) + ((current_datetime.year / 16) * 10);
    }
}

/**
 * @brief Write a datetime struct to the RTC
 * 
 * @param dt 
 */
void rtc_write_datetime(datetime_t *dt)
{
    /* Wait for the RTC to be updated */
    while (rtc_is_updating());

    rtc_set_register(0x00, dt->second);
    rtc_set_register(0x02, dt->minute);
    rtc_set_register(0x04, dt->hour);
    rtc_set_register(0x07, dt->day);
    rtc_set_register(0x08, dt->month);
    rtc_set_register(0x09, dt->year);
}

/**
 * @brief Convenient function to convert a datetime struct to a string.
 * Output format: "day hour:minute"
 * Example: "Sun 10:30"
 * 
 * @param dt 
 * @return char* 
 */
char *rtc_datetime_string(datetime_t *dt)
{
    char *ret = kmalloc(sizeof(char) * 16);
    char day[4];
    char hour[3];
    char minute[3];

    memset(&day, 0x0, 4);
    memset(&hour, 0x0, 3);
    memset(&minute, 0x0, 3);

    const char *weekday = weekday_map[rtc_weekday_from_date(dt)];
    strcpy(day, weekday);
    itoa(hour, dt->hour);
    itoa(minute, dt->minute);

    strcpy(ret, day);
    strcat(ret, " ");
    strcat(ret, hour);
    strcat(ret, ":");
    strcat(ret, minute);
    return ret;
}

char *rtc_current_datetime_string()
{
    return rtc_datetime_string(&current_datetime);
}

int rtc_weekday_from_date(datetime_t *dt)
{
    char month_code_array[] = {0x0,0x3, 0x3, 0x6, 0x1, 0x4, 0x6, 0x2, 0x5, 0x0, 0x3, 0x5};
    char century_code_array[] = {0x4, 0x2, 0x0, 0x6, 0x4, 0x2, 0x0}; /* Starting with 18th century */

    /* Set current century */
    dt->century = 21;

    /* Calculate the year code */
    int year_code = (dt->year + (dt->year / 4)) % 7;
    int month_code = month_code_array[dt->month - 1];
    int century_code = century_code_array[dt->century - 18];
    int leap_year_code = rtc_leap_year(dt->year, dt->month);

    int ret = (year_code + month_code + century_code + leap_year_code) % 7;
    return ret;
}

int rtc_leap_year(int year, int month)
{
    if (year % 4 == 0 && (month == 1 || month == 2)) return 1;
    return 0;
}

/**
 * @brief Initialize the RTC
 * 
 * @note FIXME: This function is not working properly. It is not setting the correct time.
 *  It is also not setting the correct date.
 * 
 * @note NOTE: copilot idea: The rtc_read_datetime() function is not working properly.
 *  It is not reading the correct time. This could be because of the way the RTC is set.
 *  The RTC is set using the `-rtc base=localtime` command line argument for qemu.
 *  The RTC is not being read correctly. via the rtc_read_datetime() function.
 * 
 */
void rtc_init()
{
    rtc_read_datetime();
}
