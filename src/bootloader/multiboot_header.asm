; @file multiboot_header.asm
; @author Owen Boreham (owenkadeboreham@gmail.com)
; @version 0.1.2
; @date 2021-08-23
; 
; @copyright Copyright (c) 2021 TinyKernel
; This file is part of TinyKernel which is released
; under Apache License 2.0.  See file LICENSE or go
; to https://www.apache.org/licenses/LICENSE-2.0 for
; full license details.

section .text
header_start:
    dd 0xe85250d6                   ; magic number
    dd 0                            ; protected mode code
    dd header_end - header_start    ; header size

    ; Checksum
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    ; required end tag
    dw 0    ; type
    dw 0    ; flags
    dw 8    ; size
header_end: