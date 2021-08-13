#ifndef PIT_H
#define PIT_H

#include <types.h>

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

#define BASE_FREQ           1193180

#endif // PIT_H