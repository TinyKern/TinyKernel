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