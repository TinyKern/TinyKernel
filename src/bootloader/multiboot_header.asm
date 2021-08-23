section .multiboot_header
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