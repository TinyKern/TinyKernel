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