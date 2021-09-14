#ifndef IRQ_H
#define IRQ_H

#include "../cpu.h"
#include "../idt/idt.h"

#include <types.h>

/**
 * @brief Initialize the IRQ subsystem.
 * 
 * @return uint32_t 0 on success
 */
uint32_t irq_init(void);

#endif /* IRQ_H */