extern errno_location
section .text
	global ft_read

ft_read:
	mov rax, 0
	syscall
	cmp rax, 0
	js error
	ret

error:
	neg rax
	push rax
	call errno_location
	pop rcx
	mov [rax], ecx
	mov rax, -1
	ret
