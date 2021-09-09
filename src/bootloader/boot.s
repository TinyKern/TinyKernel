/**
 * @file boot.s
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.3
 * @date 2021-07-06
 *
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

// set magic number to 0x1BADB002 to be identified by bootloader
.set        MAGIC, 0x1BADB002

// set flags to 0
.set        FLAGS, 0

// set the checksum
.set        CHECKSUM, -(MAGIC + FLAGS)

// set multiboot enabled
.section    .multiboot

// define type to long for each data defined as above
.long       MAGIC
.long       FLAGS
.long       CHECKSUM

// set the stack bottom
stackBottom:

// define the maximum size of stack to 512 bytes
.skip 1024

// set the stack top which grows from higher to lower
stackTop:

.section    .text
.global     _start
.type       _start, @function

_start:
    cli
    cld

    // assign current stack pointer location to stackTop
    mov     $stackTop, %esp

    // call the kernel main source
    push    %eax
    push    %ebx
    call    kernel_entry

    cli

// put system in infinite loop
hltLoop:
    hlt
    jmp     hltLoop

.size _start, . - _start
