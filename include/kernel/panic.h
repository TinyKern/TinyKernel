#ifndef PANIC_H
#define PANIC_H

#include <drivers/vga/vga.h>
#include <drivers/video/video.h>

#include "cpu/cpu.h"
#include "stdio.h"

extern void kpanic(int errcode, char* errmsg);

#endif // PANIC_H