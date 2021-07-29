[org 0x7c00]
    mov     bp, 0x8000      ; set the stack safely away from us
    mov     sp, bp

    mov     bx, 0x9000      ; es:bx = 0x0000:0x9000 = 0x09000
    mov     dh, 2           ; read 2 sectors
    ; the bios sets 'dl' for our boot dis number
    ; if you have trouble, use the '-fda' flag: 'qemu -fda file.elf'
    call    disk_load

    mov     dx, [0x9000]    ; retrieve the first loaded word, 0xdada
    call    print_hex

    call    print_nl

    ; first word from second loaded sector, 0xface
    mov     dx, [0x9000 + 512]
    call    print_hex

    jmp     $

; %include "../functions/print.asm"
; %include "../functions/print_hex.asm"
; %include "disk.asm"

; Magic number
times       512 - ($-$$) db 0
dw          0xaa55

; boot sector = sector 1 of cyl 0 of head 0 of hdd 0
; from now on = sector 2...
times       256 dw 0xdada   ; sector 2 = 512 bytes
times       256 dw 0xface   ; sector 3 = 512 bytes