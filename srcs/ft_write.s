extern errno_location
section .text
	global ft_write

ft_write:
	mov rax, 1			; rax = 1 (select write syscall, 1 on Linux)
	syscall				; fd, buf, count (rdi, rsi, rdx)
	cmp rax, 0			; if return of syscall < 0 (what Kernel ret)
	jl error				; go to error (if syscall failed)
	ret				; rax holds bytes written

error:
	neg rax				; -errno = +errno
	push rax			; save on the stack
	call errno_location		; rax = errno_addr
	pop rcx				; take from stack into rcx
	mov [rax], ecx			; *errno = value (ecx: 4byte int)
	mov rax, -1			; write error = -1
	ret
