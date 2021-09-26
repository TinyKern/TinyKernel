#ifndef PIC_H
#define PIC_H

#include <types.h>

#define PIC1_CMD_PORT   0x20
#define PIC1_DATA_PORT  0x21
#define PIC2_CMD_PORT   0xA0
#define PIC2_DATA_PORT  0xA1
#define PIC_EOI         0x20

#define ICW1            0x11
#define ICW4            0x01

void pic_init();
void irq_ack(uint8_t irq);

#endif /* PIC_H */