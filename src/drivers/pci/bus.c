#include <config.h>

#include <drivers/pci/bus.h>
#include <debug/qemu.h>

const char* class_names[] = {
    "Unclassified",
    "Mass Storage Controller",
    "Network Controller",
    "Display Controller",
    "Multimedia Controller",
    "Memory Controller",
    "Bridge Device",
    "Simple Communication Controller",
    "Base System Peripheral",
    "Input Device",
    "Docking Station",
    "Processor",
    "Serial Bus Controller",
    "Wireless Controller",
    "Intelligent I/O Controller",
    "Satellite Communication Controller",
    "Encryption/Decryption Controller",
    "Data Acquisition and Signal Processing Controller",
    "Reserved",
};

void pci_enum_bus(void)
{
    uint16_t bus;
    for (bus = 0; bus < 255; bus++)
        pci_check(bus);
}

void pci_check(uint8_t bus)
{
    uint8_t slot;
    for (slot = 0; slot < 32; slot++)
        pci_slot_check(bus, slot);
}

void pci_slot_check(uint8_t bus, uint8_t slot)
{
    uint8_t func;
    for (func = 0; func < 32; func++)
    {
        uint32_t device_and_vendor = pci_read_config_reg(bus, slot, func, 0x00);

        if ((device_and_vendor & 0xFFFF) == 0xFFFF)
            break;
        
        uint32_t class_register = pci_read_config_reg(bus, slot, func, 0x08);
        uint8_t class = (uint8_t)(class_register >> 24);

        kprintf("Pci devices at %d:%d:%d has vendor %x and device %x, of class %s.\n", bus, slot, func, device_and_vendor&0xFFFF, device_and_vendor>>16, class_names[class]);
#ifdef QEMU_SERIAL_ENABLED
        qemu_info("Pci devices at %d:%d:%d has vendor %x and device %x, of class %s.\n", bus, slot, func, device_and_vendor&0xFFFF, device_and_vendor>>16, class_names[class]);
#endif
    }
}

uint32_t pci_read_config_reg(uint8_t bus, uint8_t slot, uint8_t func, uint8_t reg)
{
    // Addres of register to be read from. This is an address in the "PCI"
    // config space, not the "I/O" space or general memory space.
    uint32_t address = 0x80000000 | (uint32_t)((bus & 0xFF) << 16) | (uint32_t)((slot & 0x1F) << 11) | (uint32_t)((func & 0x05) << 8) | (uint32_t)(reg & 0xFC);

    // Write the address to the PCI config space. This will cause the PCI
    // bus to respond to the address. The PCI bus will respond with the
    // value of the register. This is the value that we will read.
    out32(0xCF8, address);

    // Read the value from the PCI config space. This is the value that
    // the PCI bus responded with.
    return in32(0xCFC);
}