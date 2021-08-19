#ifndef CURSOR_H
#define CURSOR_H

#include "vga.h"
#include <types.h>

extern void enable_cursor(uint8_t start, uint8_t end);
extern void disable_cursor();

#endif // CURSOR_H
