#ifndef ISR_H
#define ISR_H

#include <types.h>

#include <debug/qemu.h>

/* ISR_DEBUG (define if debugging) */
#define ISR_DEBUG 1

#ifdef ISR_DEBUG
# define isr_debug(...) {                   \
    qemu_dbg("%s:%d, %s() ",                \
            __FILE__, __LINE__, __func__);  \
};
#else
# define isr_debug(f, ...) /* nothing */
#endif

/* IRQ Map */
#define IRQ0    32
#define IRQ1    33
#define IRQ2    34
#define IRQ3    35
#define IRQ4    36
#define IRQ5    37
#define IRQ6    38
#define IRQ7    39
#define IRQ8    40
#define IRQ9    41
#define IRQ10   42
#define IRQ11   43
#define IRQ12   44
#define IRQ13   45
#define IRQ14   46
#define IRQ15   47

typedef uint32_t register_t;

struct registers
{
    /* Segment selector */
    register_t ds;

    /* General purpose registers */
    register_t edi;
    register_t esi;
    register_t ebp;
    register_t esp;
    register_t ebx;
    register_t edx;
    register_t ecx;
    register_t eax;

    /* Interrupt number and error code (if applicable) */
    register_t int_no;
    register_t err_code;

    /* Processor */
    register_t eip;
    register_t cs;
    register_t eflags;
    register_t useresp;
    register_t ss;
};

/* ISR handler */
typedef void (*isr_t)(struct registers);

void register_interrupt_handler(uint8_t interrupt_number, isr_t handler);

#endif /* ISR_H */