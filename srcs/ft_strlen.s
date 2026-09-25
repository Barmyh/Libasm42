section .text
	global ft_strlen	; C function

ft_strlen:
	xor rax, rax		; set rax to 0 (xor gate, rax and rax always equal = 0)

.loop:
	cmp byte [rdi + rax], 0 ; ex: hello - rdi(0x1000 = h) + rax(2) = 0x1002 = l
				; rdi points to the input string
	je .done		; if equal (0) jump to .done
	inc rax			; increment rax
	jmp .loop		; uncoditional jump to .loop (repeat)

.done:
	ret			; return (rax = length)



;int strlen(char *str) {
;	int i = 0;
;	while(str[i])
;		i++;
;	return i;
;}
