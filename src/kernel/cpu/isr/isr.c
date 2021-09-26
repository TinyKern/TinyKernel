#include <kernel/cpu/isr/isr.h>
#include <kernel/cpu/cpu.h>
#include <kernel/cpu/pic.h>
#include <kernel/time/PIT.h>
#include <kernel/panic.h>
#include <kernel/stdio.h>
#include <kernel/errno.h>
#include <sys/string.h>

static char *exception_messages[] = {
    "Division by zero",
    "Debug",
    "Non-maskable interrupt",
    "Breakpoint",
    "Overflow",
    "Bounds",
    "Invalid opcode",
    "No coprocessor",
    "Double fault",
    "Coprocessor segment overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown interrupt",
    "Coprocessor fault",
    "Alignment check",
    "Machine check",
    "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved",
};

isr_t interrupt_handlers[256];

static void handle_excecution(register_t registers)
{
    if (registers.int_no < 32)
    {
        qemu_panic("EXCEPTION: %s (code %x)\r\n", exception_messages[registers.int_no], registers.err_code);
        kpanic(registers.err_code, "An exception occurred");
    }
    if (interrupt_handlers[registers.int_no] != NULL)
    {
        isr_t handler = interrupt_handlers[registers.int_no];
        handler(&registers);
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
void isr_handler(register_t registers)
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
void irq_handler(register_t registers)
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
    qemu_dbg("Register: [%d. %p]\n", interrupt_number, (uint32_t)handler);
    if (interrupt_number < 256)
        interrupt_handlers[interrupt_number] = handler;
}

void final_irq_handler(register_t *reg)
{
    if (interrupt_handlers[reg->int_no] != NULL)
    {
        isr_t handler = interrupt_handlers[reg->int_no];
        handler(reg);
    }
    irq_ack(reg->int_no);
}
