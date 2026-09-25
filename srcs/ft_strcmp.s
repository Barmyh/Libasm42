section .text
	global ft_strcmp

ft_strcmp:
	xor rax, rax

.loop:	
	; al = first 8 bits of rax
	mov al, [rdi]	; [ ] means dereference, al = *rdi
	cmp al, [rsi]	; *rdi == *rsi (1st and 2nd args)
	jne .diff	; if not equal jump to .diff

	cmp al, 0	; checks if al == 0
	je .done	; if equal to 0 jump to .done

	inc rdi		; rdi++
	inc rsi		; rsi++
	jmp .loop	; repeat

.diff:
	movzx eax, byte [rdi] ; read ONE byte [rdi] into eax (8-bit with the rest 0 extended)
	movzx ecx, byte [rsi] ; same here, this leaves a clean rax
	sub eax, ecx	; a = a - b (rax = rax - [rsi])
	
.done:
	ret




;int ft_strcmp(const char *str1, const char *str2) {
;	int i = 0;
;	while (str1[i] == str2[i] && str1[i] && str2[i]) {
;		i++;
;	}
;	return (str1[i] - str2[i]);
;}
