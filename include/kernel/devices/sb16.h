#ifndef SB16_H
#define SB16_H

#include <types.h>

#define DSP_RESET       0x226
#define DSP_READ        0x22A
#define DSP_WRITE       0x22C
#define DSP_READ_STATUS 0x22E
#define DSP_INT_ACK     0x22F

#define REG_ADDR        0x224
#define REG_DATA        0x225

#define DIRECT_DAC      0x10
#define ENABLE_SPEAKER  0xD1


#endif // SB16_H