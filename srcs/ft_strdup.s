extern __errno_location
extern malloc
extern ft_strlen
extern ft_strcpy

section .text
global ft_strdup

ft_strdup:
	push rdi
	call ft_strlen
	inc rax
	mov rdi, rax
	call malloc

	test rax, rax
	jz .error

	mov rdi, rax
	pop rsi

.copy:
	mov dl, [rsi]
	mov [rdi], dl

	inc rsi
	inc rdi

	test dl, dl
	jnz .copy
	jmp .done

.done:
	ret

.error:
	pop rdi
	xor rax, rax
	ret


; char *strdup(const char *s)
; on success, returns a pointer to the duplicated string
; null if insufficient mem, with errno