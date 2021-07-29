/**
 * @file video.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.1
 * @date 2021-07-06
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef VIDEO_H
#define VIDEO_H

#define CTRL_SCREEN_REG 0x3d4
#define DATA_SCREEN_REG 0x3d5

extern int get_cursor_offset();
extern void set_cursor_offset(int offset);

extern void clear_screen();

#endif