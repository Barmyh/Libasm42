extern __errno_location
section .text
	global ft_write

ft_write:
	mov rax, 1		; rax = 1 (select write syscall, 1 on Linux)
	syscall			; kernel performs operation idintified by RAX (1)

	cmp rax, 0
	jl error		; if rax < 0

	ret				; rax hold bytes written

error:
	neg rax			; negate error code (-9 -> 9)
	push rax		; save error number on the stack

	call __errno_location wrt ..plt	; rax = address of errno
	
	pop rcx			; rcx = error number (take from top of stack and assign to rcx)
	mov [rax], ecx	; push/pop work on 64-bit stack slots, but errno is 32-bit, that's why we use ecx instead
	mov rax, -1		; write itself still return -1 on error
	ret				; return rax



; error flow:
; -9 -> 9

; save error number (9) on the stack
; because calling errno_location will overwrite rax

; calling errno_location -> RAX = address of errno

; pop saved errno number into RCX = 9

; store the 32-bit number into errno
; [RAX] = 9 - rax is the address of errno

; Overwrite RAX = -1 so the return value isn't the address of errno
; errno = 9


; int write(int fd, char *buf, size_t bytes_count)
; on succes, nbr of bytes written. On error, -1, errno is set to indicate the error.