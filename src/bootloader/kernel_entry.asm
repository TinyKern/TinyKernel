[bits 32]
[extern kernel_entry]		; Define calling point. Must hace same name as kernel.c entrypoint function
call	kernel_entry
jmp		$