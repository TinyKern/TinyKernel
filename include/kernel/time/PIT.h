/**
 * @file PIT.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.1
 * @date 2021-08-12
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef PIT_H
#define PIT_H

#include <types.h>

#include <kernel/cpu/cpu.h>

/* Timer related ports */
#define TIMER_T0_CTL		0x40
#define TIMER_T1_CTL		0x41
#define TIMER_T2_CTL		0x42
#define PIT_CTL		        0x43

/* Building blocks for PIT_CTL */
#define TIMER_T0_SELECT		0x00
#define TIMER_T1_SELECT		0x40
#define TIMER_T2_SELECT		0x80

#define MODE_COUNTDOWN      0x00
#define MODE_ONESHOT        0x02
#define MODE_RATEGEN        0x04
#define MODE_SQAURE_WAVE    0x06

#define WRITE_WORD          0x30

/* Addresses of PIT registers */
#define PIC_MASTER_COMMAND  0x20
#define PIC_MASTER_DATA     0x21
#define PIC_SLAVE_COMMAND   0xA0
#define PIC_SLAVE_DATA      0xA1

/* Macros for setting up the PIT */
#define PIC_MASTER_CMD_OUT(byte)    outb(PIC_MASTER_COMMAND, (byte))
#define PIC_MASTER_DATA_OUT(byte)   outb(PIC_MASTER_DATA, (byte))
#define PIC_SLAVE_CMD_OUT(byte)     outb(PIC_SLAVE_COMMAND, (byte))
#define PIC_SLAVE_DATA_OUT(byte)    outb(PIC_SLAVE_DATA, (byte))

#define BASE_FREQ           1193180

extern unsigned read_pit_count(void);
extern void     set_pit_count(unsigned count);

#endif // PIT_H