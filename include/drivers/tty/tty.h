#ifndef TTY_H
#define TTY_H

#include <types.h>

struct tty;

static ALWAYS_INLINE struct tty *get_curr_tty(void)
{
    extern struct tty *__curr_tty;
    return __curr_tty;
}



#endif // TTY_H