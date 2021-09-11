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

// Constants for the bootloader
.set        ALIGN, 1<<0                 // align loaded modules on page boundaries
.set        MEMINFO, 1<<1               // load memory information
.set        FLAGS, ALIGN | MEMINFO      // load all modules
.set        MAGIC, 0x1BADB002           // magic number for the bootloader
.set        CHECKSUM, -(MAGIC + FLAGS)  // checksum for the bootloader

// set multiboot enabled. This is required for the bootloader to work.
.section    .multiboot
.align      4                       // align to 4 bytes
.long       MAGIC                   // magic number
.long       FLAGS                   // flags
.long       CHECKSUM                // checksum

stackBottom:
.skip       1024                    // stack bottom
stackTop:

.section    .text
.global     _start                  // entry point
.type       _start, @function       // function type

_start:
    // Disable interrupts: we don't want to be interrupted by anything
    // while we're loading the kernel.
    cli
    cld

    // Setup the stack pointer. We need to do this before loading the
    // kernel.
    mov     $stackTop, %esp

    // Enter the high-level kernel. This will load the kernel and
    // call the entry point.
    push    %eax                    // save eax for later
    push    %ebx                    // save ebx for later
    call    kernel_entry            // call the kernel entry point

    cli                             // disable interrupts

// put system in infinite loop. This is a good place to put a breakpoint
// to debug the kernel.
hltLoop:
    hlt                             // halt the system
    jmp     hltLoop                 // loop forever

// kernel entry point, called by the high-level kernel. This will load
// the kernel and call the entry point.
.size _start, . - _start
