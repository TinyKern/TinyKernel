/**
 * @file linker.ld
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1
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

SECTIONS
{
    /* we need 1MB of space atleast */
    . = 1M;

    /* text section */
    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }

    /* read only data section */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /* data section */
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    /* bss section */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
}
