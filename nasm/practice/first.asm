; Create program with different data sizes (db/dw/dq) and print their values |
;============================================================================+

.text			; code section whatever is in this section will be executed 
global _start		; sets _start as the program entry point

_start:
    mov rax, 1		; number of syscall <write>
    mov rdi, 1		; file discripter(fd) for stdout
    mov rsi, var1 	; pointer to buffer
    mov rdx, 2		; length of string
    syscall		; cpu switches from usermode to kernel mode

    ; return 0
    mov eax, 60		; syscall number of <exit>
    xor rdi,rdi		; 0 for success
    syscall		; transition from user mode -> kernel mode

.data			; only initialized data

var1 DB "0",10 		;10 is the ascii of newline character





