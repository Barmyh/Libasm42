extern __errno_location
section .text
	global ft_read

ft_read:
	mov rax, 0
	syscall			; checks value of rax to call rad (0)
	cmp rax, 0		; 
	js error
	ret

error:
	neg rax					; same principles as the write one
	push rax
	call __errno_location wrt ..plt
	pop rcx
	mov [rax], ecx
	mov rax, -1
	ret

; ssize_t read(int fd, void *buf, size_t count);
; on success, number of bytes read, on error = -1 and set errno