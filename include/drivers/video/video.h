#ifndef VIDEO_H
#define VIDEO_H

#define CTRL_SCREEN_REG 0x3d4
#define DATA_SCREEN_REG 0x3d5

extern int get_cursor_offset();
extern void set_cursor_offset(int offset);

extern void clear_screen();

#endif