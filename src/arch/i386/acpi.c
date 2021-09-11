#include <arch/i386/acpi.h>
#include <debug/qemu.h>

dword_t     *SMI_CMD;
byte        ACPI_ENABLE;
byte        ACPI_DISABLE;
dword_t     *PM1a_CNT;
dword_t     *PM1b_CNT;
word_t      SLP_TYPa;
word_t      SLP_TYPb;
word_t      SLP_EN;
word_t      SCI_EN;
byte        PM1_CNT_LEN;

// Check if the given address has a valid header
static uint32_t *acpi_check_rsd_ptr(uint32_t *ptr)
{
    char *sig = "RSD PTR ";
    struct RSDPtr *rsdp = (struct RSDPtr *)ptr;
    byte *bptr;
    byte check = 0;
    int i;

    if (memcmp(sig, rsdp, 8) == 0)
    {
        // Check checksum of the header
        bptr = (byte *) ptr;
        for (i = 0; i < sizeof(struct RSDPtr); i++)
        {
            check += *bptr;
            bptr++;
        }

        // Found a valid header
        if (check == 0)
            return (uint32_t *) rsdp->rsdt_address;
    }

    return NULL;
}

// Finds the acpi header and returns a pointer to it
uint32_t *acpi_get_rsd_ptr(void)
{
    uint32_t *addr;
    uint32_t *rsdp;

    // Search below 1MB for an RSDP signature
    for (addr = (uint32_t *) 0x000E0000; (int) addr < 0x00100000; addr += 0x10/sizeof(addr))
    {
        rsdp = acpi_check_rsd_ptr(addr);
        if (rsdp != NULL)
            return rsdp;
    }

    // At address 0x40:0x0E is the RM segment of the ebda
    int ebda = *((short *) 0x40E); // EBDA address
    ebda = ebda*0x10 & 0x000FFFFF; // Convert to linear address

    // Search extended BIOS data area for the Root System Description Pointer signature
    for (addr = (uint32_t *) ebda; (int) addr < ebda + 1024; addr += 0x10/sizeof(addr))
    {
        rsdp = acpi_check_rsd_ptr(addr);
        if (rsdp != NULL)
            return rsdp;
    }

    return NULL;
}

// Checks for a given header and validates checksum
static bool acpi_check_header(uint32_t *ptr, char *sig)
{
    if (memcmp(ptr, sig, 4) == 0)
    {
        char *check_ptr = (char *) ptr;
        int len = *(check_ptr + 1);
        char check = 0;
        while (0 < len--)
        {
            check += *check_ptr;
            check_ptr++;
        }

        if (check == 0)
            return true;
    }
    
    return false;
}

int acpi_enable(void)
{
    // Check if acpi is enabled
    if ((inw((uint32_t) PM1a_CNT) &SCI_EN) == 0)
    {
        // check if acpi is supported
        if (SMI_CMD != 0 && ACPI_ENABLE != 0)
        {
            // Enable acpi
            outb((uint32_t) SMI_CMD, ACPI_ENABLE); // Send acpi enable command

            // Wait for acpi to be enabled
            int i;
            for (i = 0; i < 300; i++)
            {
                if ((inw((uint32_t) PM1a_CNT) &SCI_EN) == 1)
                    break;
                sleep(10);
            }

            if (PM1b_CNT != 0)
            {
                for (; i < 300; i++)
                {
                    if ((inw((uint32_t) PM1b_CNT) &SCI_EN) == 1)
                        break;
                    sleep(10);
                }
            }

            if (i < 300)
            {
                qemu_success("ACPI enabled\n");
                return 0;
            }
            else
            {
                qemu_error("ACPI failed to enable\n");
                return -1;
            }
        }
        else
        {
            qemu_error("ACPI not supported\n");
            return -1;
        }
    }
    else
    {
        qemu_info("ACPI already enabled\n");
        return 0;
    }
}

/**
 * This function initializes the ACPI subsystem. It will search for the
 * RSDP signature and load the RSDT tables. It will also enable the
 * ACPI subsystem.
 * More information can be found in the ACPI specification.
 * 
 * @return int 0 on success, -1 on failure
 */
int acpi_init(void)
{
    uint32_t *ptr = acpi_get_rsd_ptr();

    // Check if address is valid ( if acpi is supported )
    if (ptr != NULL && acpi_check_header(ptr, "RSDT") == 0)
    {
        // the RSDT contains an unknown number of pointers to other tables
        // we need to read the number of pointers from the header
        int entries = *(ptr + 1);
        entries = (entries - 36) / 4;
        ptr += 36/4; // Skip header info

        // Loop through all the entries and load the tables
        while (0 < entries--)
        {
            // Check if the desired table has been reached
            if (acpi_check_header((uint32_t *) *ptr, "FACP") == 0)
            {
                // Found the FACP table
                entries = -2;
                struct FACP *facp = (struct FACP *) *ptr;
                if (acpi_check_header((uint32_t *) facp->dsdt_address, "DSDT") == 0)
                {
                    // Search the \_S5 package in the DSDT
                    char *S5addr = (char *) facp->dsdt_address + 36; // Skip header
                    int dsdt_len = *(facp->dsdt_address + 1) - 36;

                    while (0 < dsdt_len--)
                    {
                        if (memcmp(S5addr, "_S5_", 4) == 0)
                            break;
                        S5addr++;
                    }
                    
                    // Check is \_S5 was found
                    if (dsdt_len > 0)
                    {
                        // Check for valid AML structure
                        if ((*(S5addr-1) == 0x08 || (*(S5addr-2) == 0x08 && *(S5addr-1) == '\\')) 
                            && *(S5addr+4) == 0x12 )
                        {
                            S5addr += 5; // Skip the \_S5 package
                            S5addr += ((*S5addr & 0xC0) >> 6) + 2; // calculate the length of the package

                            // Check if the \_S5 package is valid
                            if (*S5addr == 0x0A)
                                S5addr++; // skip the byteprefix
                            SLP_TYPa = *(S5addr) << 10;
                            S5addr++;

                            if (*S5addr == 0x0A)
                                S5addr++; // skip the byteprefix
                            SLP_TYPb = *(S5addr) << 10;

                            SMI_CMD = facp->SMI_CMD;

                            // Enable acpi
                            ACPI_ENABLE = facp->ACPI_ENABLE;
                            ACPI_DISABLE = facp->ACPI_DISABLE;

                            PM1a_CNT = facp->PM1a_CNT_BLK;
                            PM1b_CNT = facp->PM1b_CNT_BLK;

                            PM1_CNT_LEN = facp->PM1_CNT_LEN;

                            SLP_EN = 1 << 13;
                            SCI_EN = 1;

                            return 0;
                        }
                        else
                        {
                            qemu_error("Invalid DSDT, \\_S5 parse error\n");
                        }
                    }
                    else
                    {
                        qemu_error("Invalid DSDT, \\_S5 not present\n");
                    }
                }
                else
                {
                    qemu_error("Invalid DSDT\n");
                }
            }
            ptr++;
        }

        qemu_error("FACP not found\n");
    }
    else
    {
        qemu_warning("ACPI not found\n");
    }

    return -1;
}

void acpi_power_off(void)
{
    // SCI_EN is set to 1 if acpi shutdown is possible
    if (SCI_EN == 0)
        return;
    
    acpi_enable();

    // send the shutdown command
    outw((uint32_t) PM1a_CNT, SLP_TYPa | SLP_EN);
    if (PM1b_CNT != 0)
        outw((uint32_t) PM1b_CNT, SLP_TYPb | SLP_EN);
    
    qemu_error("ACPI shutdown failed\n");
}
