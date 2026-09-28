section .text
	global ft_strcpy

ft_strcpy:
	mov rax, rdi	; save og dst pointer

.loop:
	mov cl, [rsi]	; read src[i]
	mov [rdi], cl	; write dst[i]

	cmp cl, 0		; '\0'?
	je .done
	
	inc rsi
	inc rdi
	jmp .loop

.done:
	ret


; NOTE: using al, dil (8-bits of rax/rdi) won't work because they are part of rax/rdi and NOT seperate enteties.
;		changing then would also change rax/rdi.

;char *ft_strcpy(char *dst, const char *src) {
;	int i = 0;
;	while (src[i])
;		dst[i] = src[i]
;		i++
;	dst[i] = \0
;	return dst;	
;}
