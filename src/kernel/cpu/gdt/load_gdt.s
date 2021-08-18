/**
 * @file load_gdt.s
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.1
 * @date 2021-08-15
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

.section .text
.global load_gdt

load_gdt:
    mov     4(%esp), %eax
    lgdt    (%eax)
    
    mov     $0x10, %eax
    mov     %eax, %ds
    mov     %eax, %es
    mov     %eax, %fs
    mov     %eax, %gs
    mov     %eax, %ss
    jmp     $0x8, $.long_jump
.long_jump:
    ret
