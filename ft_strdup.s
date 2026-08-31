extern errno_location
extern malloc
extern ft_strlen
extern ft_strcpy

section .text
global ft_strdup

ft_strdup:
	push rdi

calc_len:
	call ft_strlen
	mov rcx, rax
	inc rcx

malloc_dest:
	mov rdi, rcx
	call malloc
	cmp rax, 0
	je error

cpy_str:
	mov rdi, rax
	pop rsi
	call ft_strcpy
	ret

error:
	pop rdi
	call errno_location
	mov rdx, 12
	mov [rax], rdx
	mov rax, 0
	ret
