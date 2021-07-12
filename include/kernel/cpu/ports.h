#ifndef KERNEL_CPU_H
#define KERNEL_CPU_H

#include <sys/types.h>

// returns in inbound keyboard input from
// the keyboard port 0x60
extern uint8 inb(uint16 port);
extern void outb(uint16 port, uint8 data);

#endif