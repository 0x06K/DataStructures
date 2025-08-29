;+==================================================================================+

.text			; code section whatever is in this section will be executed 
global _start		; sets _start as the program entry point

_start:
    mov rax, 0		; number of syscall <read>
    mov rdi, 0		; file discripter(fd) for stdin
    mov rsi, buffer 	; pointer to buffer
    mov rdx, 99 	; length of string
    syscall		; cpu switches from usermode to kernel mode

    ; return 0
    mov eax, 60		; syscall number of <exit>
    xor rdi,rdi		; 0 for success
    syscall		; transition from user mode -> kernel mode

.bss			; uninitialized data

buffer DW 100		; char buffer[100]




