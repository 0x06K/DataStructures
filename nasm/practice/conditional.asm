; grading system (85 == A, 80 == A-, 75 == B, <75 fail)

section .bss
    buff resb 4          ; reserve 4 bytes for input

section .data
    query db "Enter your marks: "
    qlen equ $ - query

    gA db "A+", 10
    gAlen equ $ - gA

    gB db "B+", 10
    gBlen equ $ - gB

    gF db "Fail", 10
    gFlen equ $ - gF

section .text
    global _start

_start:
    ; write prompt
    mov rax, 1          ; sys_write
    mov rdi, 1          ; stdout
    mov rsi, query
    mov rdx, qlen
    syscall

    ; read input
    mov rax, 0          ; sys_read
    mov rdi, 0          ; stdin
    mov rsi, buff
    mov rdx, 4
    syscall

    ; convert ASCII to integer
    xor rbx, rbx
    xor rcx, rcx

convert:
    movzx rax, byte [buff + rcx]
    cmp rax, 10         ; newline?
    je print
    sub rax, '0'
    imul rbx, rbx, 10
    add rbx, rax
    inc rcx
    jmp convert

print:
    cmp rbx, 85 ; if marks > 85
    jge gradeA
    cmp rbx, 80 ; if marks > 80
    jge gradeB
    jmp gradeF	; else

gradeA:
    mov rax, 1
    mov rdi, 1
    mov rsi, gA
    mov rdx, gAlen
    syscall
    jmp exit

gradeB:
    mov rax, 1
    mov rdi, 1
    mov rsi, gB
    mov rdx, gBlen
    syscall
    jmp exit

gradeF:
    mov rax, 1
    mov rdi, 1
    mov rsi, gF
    mov rdx, gFlen
    syscall

exit:
    mov rax, 60
    xor rdi, rdi
    syscall

