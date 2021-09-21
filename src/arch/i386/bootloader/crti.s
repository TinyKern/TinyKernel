.section .init
.global _init
.type _init, @function
_init:
    push    %ebp
    movl    %esp, %ebp
    /* GCC will contain the contents of crtbegin.o's .init section. */

.section .fini
.global _fini
.type _fini, @function
_fini:
    push    %ebp
    movl    %esp, %ebp
    /* GCC will contain the contents of crtbegin.o's .fini section. */
