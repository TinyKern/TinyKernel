.section .init
    /* GCC will contain the contents of crtbegin.o's .init section. */
    popl    %ebp
    ret

.section .fini
    /* GCC will contain the contents of crtbegin.o's .fini section. */
    popl    %ebp
    ret
