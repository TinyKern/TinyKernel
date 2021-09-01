; @file cursor.asm
; @author Owen Boreham (owenkadeboreham@gmail.com)
; @version 0.1.2
; @date 2021-08-19
; 
; @copyright Copyright (c) 2021 TinyKernel
; This file is part of TinyKernel which is released
; under Apache License 2.0.  See file LICENSE or go
; to https://www.apache.org/licenses/LICENSE-2.0 for
; full license details.

global disable_cursor
disable_cursor:
    pushf
    push eax
    push edx

    mov dx, 0x3D4
    mov al, 0xA
    out dx, al

    inc dx
    mov al, 0x20
    out dx, al

    pop edx
    pop eax
    popf
    ret
