#include <kernel/cpu/ports.h>
#include <kernel/cpu/pic.h>
#include <debug/qemu.h>

/**
 * @brief Initialize the PIC (Programmable Interrupt Controller)
 */
void pic_init()
{
    // ICW1: Initialization Command Word 1
    // - ICW4 required
    // - Cascade mode
    // - Level triggered mode
    // - 8086/88 mode
    outb(PIC1_CMD_PORT, ICW1);
    outb(PIC2_CMD_PORT, ICW1);

    // ICW2: Initialization Command Word 2 (IRQs 0-7)
    // - Interrupt vector offset
    outb(PIC1_DATA_PORT, 0x20);
    outb(PIC2_DATA_PORT, 0x28);

    // ICW3: Initialization Command Word 3 (connect master pic with slave pic)
    // - Slave PIC is connected to IRQ2
    outb(PIC1_DATA_PORT, 0x04);
    outb(PIC2_DATA_PORT, 0x02);

    // ICW4: Initialization Command Word 4 (x86 mode)
    outb(PIC1_DATA_PORT, ICW4);
    outb(PIC2_DATA_PORT, ICW4);

    // Clear the interrupt masks
    outb(PIC1_DATA_PORT, 0x00);
    outb(PIC2_DATA_PORT, 0x00);

    qemu_success("PIC Loaded");
}

/**
 * @brief Tell the PIC interrupt is handled
 */
void irq_ack(uint8_t irq)
{
    if (irq >= 0x28)
        outb(PIC2_CMD_PORT, PIC_EOI);
    outb(PIC1_CMD_PORT, PIC_EOI);
}