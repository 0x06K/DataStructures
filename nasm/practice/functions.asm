; File: calling_conventions_linux32.asm
; NASM 32-bit Linux
; Assemble: nasm -f elf32 functions.asm
; Link: ld -m elf_i386 functions.o -o functions

section .data
buffer times 12 db 0   ; buffer for integer to string

section .text
global _start

; ===============================
; Helper: integer to string
; eax = number
itoa:
    push ebp
    mov ebp, esp
    mov edi, buffer
    mov ecx, 10
    xor ebx, ebx
    xor edx, edx
    cmp eax, 0
    jne itoa_loop
    mov byte [edi], '0'
    inc edi
    jmp itoa_done

itoa_loop:
    xor edx, edx
    div ecx            ; eax = eax / 10, edx = remainder
    add dl, '0'
    mov [edi], dl
    inc edi
    cmp eax, 0
    jne itoa_loop

itoa_done:
    mov byte [edi], 10   ; newline
    inc edi
    mov byte [edi], 0
    pop ebp
    ret
; ===============================

; ===============================
; Helper: print buffer to stdout
print_int:
    mov eax, 4        ; sys_write
    mov ebx, 1        ; stdout
    lea ecx, [buffer]
    mov edx, 12
    int 0x80
    ret
; ===============================

; ===============================
; cdecl: caller cleans stack
cdecl_add:
    push ebp
    mov ebp, esp
    mov eax, [ebp+8]
    add eax, [ebp+12]
    pop ebp
    ret
; ===============================

; ===============================
; stdcall: callee cleans stack (simulate)
stdcall_add:
    push ebp
    mov ebp, esp
    mov eax, [ebp+8]
    add eax, [ebp+12]
    pop ebp
    ret 8
; ===============================

; ===============================
; fastcall: first 2 args in registers (simulate: eax, ebx), stack = c
fastcall_add:
    push ebp
    mov ebp, esp
    add eax, ebx
    add eax, [ebp+8]   ; c from stack
    pop ebp
    ret 4               ; remove c from stack
; ===============================

; ===============================
; thiscall: ECX = this pointer, stack = x
thiscall_add:
    push ebp
    mov ebp, esp
    mov eax, ecx
    add eax, [ebp+8]
    pop ebp
    ret
; ===============================

; ===============================
_start:
    ; --- cdecl ---
    push 20
    push 10
    call cdecl_add
    add esp, 8
    call itoa
    call print_int

    ; --- stdcall ---
    push 20
    push 10
    call stdcall_add   ; callee cleans stack
    call itoa
    call print_int

    ; --- fastcall ---
    mov eax, 10       ; a
    mov ebx, 20       ; b
    push 30           ; c
    call fastcall_add
    call itoa
    call print_int
    add esp, 4        ; remove c manually if needed

    ; --- thiscall ---
    mov ecx, 100      ; this pointer
    push 50           ; x
    call thiscall_add
    call itoa
    call print_int
    add esp, 4

    ; exit
    mov eax, 1        ; sys_exit
    xor ebx, ebx
    int 0x80
