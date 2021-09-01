/**
 * @file serial.c
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

int com_is_transmit_empty(uint16_t port)
{
    return inb(port + 5) & 0x20;
}

void com_send_char(uint16_t port, char byte)
{
    while (com_is_transmit_empty(port) == 0);
    outb(port, byte);
}