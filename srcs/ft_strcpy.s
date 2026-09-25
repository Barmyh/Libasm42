section .text
	global ft_strcpy

ft_strcpy:
	xor rax, rax

.loop:
	mov dil, [rsi]
	mov [rdi], dil	

	cmp dil, 0
	je .done
	
	inc rsi
	inc rdi
	jmp .loop

.done:
	mov rax, rdi
	ret

;char *ft_strcpy(char *dst, const char *src) {
;	int i = 0;
;	while (src[i])
;		dst[i] = src[i]
;		i++
;	dst[i] = \0
;	return dst;	
;}
