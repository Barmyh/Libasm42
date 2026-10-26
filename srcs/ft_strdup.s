extern __errno_location
extern malloc
extern ft_strlen
extern ft_strcpy

section .text
global ft_strdup

ft_strdup:
	push rdi		; save og str pointer
	call ft_strlen		; rax = strlen(src)

	inc rax			; include \0
	mov rdi, rax		; malloc(size)
	call malloc

	test rax, rax
	jz .error

	mov rdi, rax		; dest = allocated mem
	pop rsi			; src = og str
	call ft_strcpy
	jmp .done

.done:
	ret

.error:
	pop rdi			; restore stack
	xor rax, rax		; ret NULL
	ret


; char *strdup(const char *s)
; on success, returns a pointer to the duplicated string
; null if insufficient mem, with errno
