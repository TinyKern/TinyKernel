/**
 * @file serial.h
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

#ifndef SERIAL_H
#define SERIAL_H

#include <kernel/cpu/ports.h>

#define COM1_PORT 0x3F8
#define COM2_PORT 0x2F8
#define COM3_PORT 0x3E8
#define COM4_PORT 0x2E8

extern int com_is_transmit_empty(uint16_t port);
extern void com_send_char(uint16_t port, char byte);

#endif // SERIAL_H