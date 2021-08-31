#ifndef PCI_BUS_H
#define PCI_BUS_H

#include <types.h>
#include <kernel/cpu/ports.h>
#include <kernel/stdio.h>

void pci_enum_bus(void);
void pci_check(uint8_t bus);
void pci_slot_check(uint8_t bus, uint8_t slot);

/**
 * Reads the PCI config registers for specified device.
 * @param bus 8-bit PCI bus number.
 * @param slot 5-bit Device slot number on bus.
 * @param func 3-bit Function of specified device/slot.
 * @param reg 6-bit PCI config register to read. (Multiple of 4)
 * @return 32-bit value read from specified register.
 */
uint32_t pci_read_config_reg(uint8_t bus, uint8_t slot, uint8_t func, uint8_t reg);

typedef struct PciBusEntry_s
{
    uint8_t     bus;
    uint8_t     slot;
    uint8_t     func;
    uint16_t    vendor_id;
    uint16_t    device_id;
    struct      PciDeviceEntry_s *next;
} pci_bus_entry_t;

#endif // PCI_BUS_H