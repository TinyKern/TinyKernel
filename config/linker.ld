/**
 * @file linker.ld
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.1
 * @date 2021-07-06
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

/* entry point of our kernel */
ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

/* Tell where the various sections of the object files
    will be put in final kernel image. */
SECTIONS
{
    /* we need 1MB of space atleast */
    . = 1M;

    /* First we put the multiboot header, as it is required
        to be put very early in the image or the bootloader
        won't recognize the file format. */
    /* text section */
    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }

    /* Read-only data. */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /* Read-Write data (initialized) */
    .data BLOCK(4K) : ALIGN(4K)
    {
        start_ctors = .;
        KEEP(*(.init_array));
        KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));
        end_ctors = .;

        *(.data)
    }

    /* Read-Write data (uninitialized) & stack */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
}
