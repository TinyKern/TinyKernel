#ifndef ACPI_H
#define ACPI_H

#include <types.h>

#include <kernel/cpu/cpu.h>
#include <kernel/stdio.h>
#include <sys/stddef.h>
#include <sys/string.h>

struct RSDPtr
{
    byte signature[8];
    byte checksum;
    byte oem_id[6];
    byte revision;
    dword_t *rsdt_address;
};

struct FACP
{
    byte signature[4];
    dword_t length;
    byte unneded1[40 - 8];
    dword_t *dsdt_address;
    byte unneded2[48 - 44];
    dword_t *SMI_CMD;
    byte ACPI_ENABLE;
    byte ACPI_DISABLE;
    byte unneded3[64 - 54];
    dword_t *PM1a_CNT_BLK;
    dword_t *PM1b_CNT_BLK;
    byte unneded4[89 - 72];
    byte PM1_CNT_LEN;
};

int acpi_init(void);
int acpi_enable(void);
void acpi_power_off(void);

#endif /* ACPI_H */