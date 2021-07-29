; receiving the data in 'dx'
; Examples: called with dx=0x1234
print_hex:
    pusha

    mov     cx, 0               ; index

; Psuedo:
; GET LAST CHAR 'dx'; CONVERT ASCII 
; IF NUMERIC ASCII VALUES: '0' (0x30) -> '9' (0x30). ADD 0X30 TO BYTE N
; IF ALPHABETIC CHAR (A-F): 'A' (0X41) -> 'F' (0X46). ADD 0X40
; MOVE ASCII BYTE -> CORRECT POSSITION
hex_loop;
    cmp     cx, 4               ; loop 4 times

    je      end

    ; 1. Convert last char of 'dx' to ascii
    mov     ax, dx              ; use 'ax' as working register
    and     ax, 0x000f          ; 0x1234 -> 0x0004 by masking first three zeros
    add     al, 0x30            ; add 0x30 to N to convert to ascii "N"
    cmp     al, 0x39            ; if > 9, add extra 8 to represent 'A' - 'F'
    jle     step2
    add     ad, 7               ; 'A' = ASCII 65 instead of 58, so (65-58)=7

step2:
    ; 2. Get the correct position of the string to place our ASCII char
    ; bs <- base address + len(string) - (index)char
    mov     bx, HEX_OUT+5       ; Base + len
    sub     bx, cx              ; index
    mov     [bx], al            ; copy the ASCII char on 'al' -> position pointed <- 'bx'
    ror     dx, 4               ; 0x1234 -> 0x4123 -> 0x3412 -> 0x2341 -> 0x1234

    add     cx, 1
    jmp     hex_loop

end:
    mov     bx, HEX_OUT
    call    print

    popa
    ret

HEX_OUT:
    db      '0x0000', 0         ; reserve memory for our new string