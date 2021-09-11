/**
 * @file qemu.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.2
 * @date 2021-08-22
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <drivers/serial/serial.h>
#include <debug/qemu.h>
#include <sys/string.h>

void qemu_puts(const char *str)
{
    for (size_t i = 0; i < strlen(str); i++)
        com_send_char(COM1_PORT, str[i]);
}

void qemu_putuint(int i)
{
    uint32_t n, d = 1000000000;
    char str[255];
    uint32_t dec_index = 0;
    while ((i/d == 0) && (d >= 10)) d /= 10;
    n = i;

    while (d >= 10)
    {
        str[dec_index++] = ((char)((int)'0' + n/d));
        n %= d;
        d /= 10;
    }

    str[dec_index++] = ((char)((int)'0' + n));
    str[dec_index] = 0;
    qemu_puts(str);
}

void qemu_putint(int i)
{
    if (i < 0)
    {
        i = -i;
        qemu_puts("-");
    }

    qemu_putuint(i);
}

void qemu_puthex(uint32_t i)
{
    const uint8_t hex_chars[16] = { '0', '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' , 'A' , 'B' , 'C' , 'D' , 'E' , 'F' };
    uint32_t n, d = 0x10000000;

    qemu_puts("0x");
    while ((i/d == 0) && (d >= 0x10)) d /= 0x10;
    n = i;

    while (d >= 0xF)
    {
        com_send_char(COM1_PORT, hex_chars[n/d]);
        n %= d;
        d /= 0x10;
    }

    com_send_char(COM1_PORT, hex_chars[n]);
}

void qemu_print(const char *str, va_list args)
{
    int i = 0;
    char* string;

    while (str[i] != 0)
    {
        if (str[i] == '%')
        {
            i++;
            switch (str[i])
            {
                case 's':
                    string = va_arg(args, char*);
                    qemu_puts(string);
                    break;
                
                case 'c':
                    com_send_char(COM1_PORT, va_arg(args, int));
                    break;

                case 'd':
                    qemu_putint(va_arg(args, int));
                    break;
                
                case 'i':
                    qemu_putint(va_arg(args, int));
                    break;
                
                case 'u':
                    qemu_putuint(va_arg(args, uint32_t));
                    break;
                
                case 'x':
                    qemu_puthex(va_arg(args, uint32_t));
                    break;

                default:
                    com_send_char(COM1_PORT, str[i]);
                    break;
            }
        }
        else
            com_send_char(COM1_PORT, str[i]);
        i++;
    }
}

void qemu_printf(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    qemu_print(fmt, args);
    va_end(args);
}

char* output;

void _qemu_dbg(char *fmt, ...)
{
    strcpy(output, DEBUG_MESSAGE_PREFIX );
    strcat(output, fmt);

    va_list args;
    va_start(args, fmt);
    qemu_print(output, args);
    va_end(args);
}

void _qemu_success(char *fmt, ...)
{
    strcpy(output, SUCCESS_MESSAGE_PREFIX );
    strcat(output, fmt);

    va_list args;
    va_start(args, fmt);
    qemu_print(output, args);
    va_end(args);
}

void _qemu_info(char *fmt, ...)
{
    strcpy(output, INFO_MESSAGE_PREFIX );
    strcat(output, fmt);

    va_list args;
    va_start(args, fmt);
    qemu_print(output, args);
    va_end(args);
}

void _qemu_error(char* fmt, ...)
{
    strcpy(output, ERROR_MESSAGE_PREFIX );
    strcat(output, fmt);

    va_list args;
    va_start(args, fmt);
    qemu_print(output, args);
    va_end(args);
}

void _qemu_panic(char* fmt, ...)
{
    strcpy(output, PANIC_MESSAGE_PREFIX );
    strcat(output, fmt);

    va_list args;
    va_start(args, fmt);
    qemu_print(output, args);
    va_end(args);
}

void _qemu_device(char* fmt, ...)
{
    strcpy(output, DEVICE_MESSAGE_PREFIX );
    strcat(output, fmt);

    va_list args;
    va_start(args, fmt);
    qemu_print(output, args);
    va_end(args);
}

void _qemu_warning(char* fmt, ...)
{
    strcpy(output, WARNING_MESSAGE_PREFIX );
    strcat(output, fmt);

    va_list args;
    va_start(args, fmt);
    qemu_print(output, args);
    va_end(args);
}
