; mul table of 2, lol anyway just did it :P

section .text

xor rcx, rcx
mov rbx, 2

table:
    imul rbx, rbx, rcx
    convert:
        mov rax, rbx
        mov rdi, 10
        div rdi
        cmp rax, 0
        jz end
        add dl, 0x30
        push dl;
        mov rbx, rax
        jmp convert
    end:
        add dl, 0x30
        push dl
        mov rbx, 2
        inc rcx
        cmp rcx, 10
        jle table

