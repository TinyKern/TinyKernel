#ifndef IO_H
#define IO_H

#include <types.h>

/**
 * keep the cpu busy for doing nothing(nop)
 * so that io port will not be processed by cpu
 * here timer can also be used, but lets do this in looping counter
 */
extern void wait_for_io(uint32 timer_count);

extern void sleep(uint32 timer_count);

#endif // IO_H