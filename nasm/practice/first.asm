.text
global _start

_start:
    mov rax, 1
    mov rdi, 1
    mov rsi, var1
    mov rdx, 16
    syscall
    mov eax, 60
    xor rdi,rdi
    syscall 

.data
var1 DB "Hello Friend !!",10,0








