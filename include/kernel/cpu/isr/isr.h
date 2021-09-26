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

/* Interrupt Service Routine prototype */
typedef void (*isr_t)(register_t*);

/* Interrupt handlers */
extern isr_t interrupt_handlers[256];
void register_interrupt_handler(uint8_t interrupt_number, isr_t handler);
void final_irq_handler(register_t *reg);

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

/* IRQ Constants */
#define IRQ_BASE                0x20
#define IRQ_SLAVE_BASE          0x00
#define IRQ1_Keyboard           0x01
#define IRQ2_CASCADE            0x02
#define IRQ3_SERIAL_PORT2       0x03
#define IRQ4_SERIAL_PORT1       0x04
#define IRQ5_RESERVED           0x05
#define IRQ6_DISKETTE_DRIVE     0x06
#define IRQ7_PARALLEL_PORT      0x07
#define IRQ8_CMOS_CLOCK         0x08
#define IRQ9_CGA                0x09
#define IRQ10_RESERVED          0x0A
#define IRQ11_RESERVED          0x0B
#define IRQ12_AUXILIARY         0x0C
#define IRQ13_FPU               0x0D
#define IRQ14_HARD_DISK         0x0E
#define IRQ15_RESERVED          0x0F

#endif /* ISR_H */