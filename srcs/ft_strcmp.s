section .text
	global ft_strcmp

ft_strcmp:
	xor rcx, rcx

.loop:
	movzx rax, byte [rdi + rcx]
	movzx rdx, byte [rsi + rcx]

	cmp rax, rdx
	jne .diff

	cmp rax, 0
	je .equal

	inc rcx
	jmp .loop

.diff:
	sub rax, rdx	; rax = s1[i] - s2[i]
	ret

.equal:
	ret
