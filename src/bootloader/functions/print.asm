print:
    pusha

; Keep this in mind:
; while (string[i] != 0) { print string[1]; i++ }

; The comparison for string end (null byte)
start:
    mov     al, [bx]        ; 'bx' Is the base address for the string
    cmp     al, 0
    je      done

    ; print using BIOS
    mov     ah, 0x0e
    int     0x10            ; 'al' already contains the char

    ; increment pointer && next loop
    add     bx, 1
    jmp     start

done:
    popa
    ret

print_nl:
    pusha

    mov     ah, 0x0e
    mov     al, 0x0a
    int     0x10
    mov     al, 0x0d
    int     0x10

    popa
    ret