section .text
	global ft_strcpy

ft_strcpy:
	xor rax, rax			; rax xor rax = 0 (exclusive or, set value of rax to 0)
.loop:
	mov cl, byte [rsi + rax]	; assign to cl the value of the rsi(adress) + rax(idx) (same as s[i])
	mov byte [rdi + rax], cl	; assign a byte of cl to rdi(adress) + rax(idx) (dest)
	cmp cl, 0			; if cl == \0 goto done
	je .done
	inc rax				; i++
	jmp .loop			; unconditional jump (repeat .loop)
.done:
	mov rax, rdi			; assign to rax the value of rdi (dest)
	ret
