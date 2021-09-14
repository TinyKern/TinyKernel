#include <kernel/cpu/isr/isr.h>
#include <kernel/cpu/cpu.h>
#include <kernel/time/PIT.h>
#include <kernel/panic.h>
#include <kernel/stdio.h>
#include <kernel/errno.h>
#include <sys/string.h>

isr_t interrupt_handlers[256];

static void handle_excecution(struct registers registers)
{
    if (interrupt_handlers[registers.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[registers.int_no];
        handler(registers);
    }
}

/**
 * @brief Handles an interrupt
 * 
 * @note This function is called by the assembly interrupt handler
 *  and is not meant to be called by the user.
 * 
 * @param registers
 * @return void
 */
void isr_handler(struct registers registers)
{
    if (registers.int_no < 32)
    {
        char *exception_message = exception_messages[registers.int_no];
        kpanic(registers.int_no, exception_message);
    }
    else
    {
        handle_excecution(registers);
    }
}

/**
 * @brief Interrupt request handler
 * 
 * @note This function is called by the assembly interrupt handler
 * 
 * @param registers
 * @return void
 */
void irq_handler(struct registers registers)
{
    /* If interrupt originated from slave PIC, send EOI to slave PIC */
    if (registers.int_no >= 40)
        PIC_SLAVE_CMD_OUT(0x20);

    /* Send EOI to master PIC */
    PIC_MASTER_CMD_OUT(0x20);

    if (registers.int_no < 32)
    {
        char *exception_message = exception_messages[registers.int_no];
        kpanic(registers.int_no, exception_message);
    }
    else
    {
        handle_excecution(registers);
    }
}

/**
 * @brief Registers an interrupt handler
 * 
 * @param int_no Interrupt number
 * @param handler Interrupt handler
 * 
 * @return void
 */
void register_interrupt_handler(uint8_t interrupt_number, isr_t handler)
{
    isr_debug("Register: [%d. %p]\n",
        interrupt_number, (uint32_t)handler);

    interrupt_handlers[interrupt_number] = handler;
}