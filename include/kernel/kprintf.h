#ifndef KPRINTF_H
#define KPRINTF_H

extern int __kprintf(char *fmt, ...);

/**
 * @brief Prints a format string to the kernel console
 * @param fmt Format string
 * @param %c - print a char
 * @param %d - print a decimal number
 * @param %o - print a octal number
 * @param %s - print a string
 * @param %x - print a hexadecimal number
 */
#define kprintf(...) __kprintf(__VA_ARGS__)

#endif // KPRINTF_H