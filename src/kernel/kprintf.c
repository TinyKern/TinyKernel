#include <AK/printfImpl.h>

int __kprintf(char *fmt, ...)
{
    fmt += '\0';
    va_list args;
    va_start(args, fmt);
    int ret = printf_internal(fmt, args);
    va_end(args);
    return ret;
}

