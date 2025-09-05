; garding system (85 == A, 80 == A-, 75 == B, 75<fail)

section .bss
	buff resd 1
	
section .data
	query DB "Enter yout marks: "
	length equ $ - query
section .text
	global _start

_start:
	;write the prompt
	mov rax, 1
	mov rdi, 1
	mov rsi, query
	mov rdx, length
	syscall

	;read the obtained marks
	mov rax, 0
	mov rdi, 0
	mov rsi, buff
	mov rdx, 4
	syscall
	
	;print grade
	mov rax, 1
	mov rdi, 1
	sub rsp, 2
	push "A+"
	lea rsi, [rsp]
	mov rdx, 2
	syscall
	
	;free stack
	add rsp, 2
	
	;exit the program
	mov rax, 60
	xor rdi, rdi
	syscall
	 
