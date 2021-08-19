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
