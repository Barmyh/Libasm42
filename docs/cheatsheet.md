64-bit	32-bit	16-bit	8-bit (low)
rax	eax	ax	al
rbx	ebx	bx	bl
rcx	ecx	cx	cl
rdx	edx	dx	dl
rsi	esi	si	sil
rdi	edi	di	dil
rbp	ebp	bp	bpl
rsp	esp	sp	spl
r8	r8d	r8w	r8b
r9–r15	r9d…	r9w…	r9b…

Data sizes (the size keywords you put before [...])

Keyword	Bits	Bytes	C type it matches
byte	8	1	char
word	16	2	short
dword	32	4	int
qword	64	8	long, pointer

This is why you write cmp byte [rdi + rax], 0 — you're telling NASM to read exactly one byte (a char), not 8.

Function calling convention (normal C calls)

Purpose	Register
1st argument	rdi
2nd argument	rsi
3rd argument	rdx
4th argument	rcx
5th argument	r8
6th argument	r9
return value	rax

Beyond 6 arguments, the rest go on the stack — but none of your libasm functions need that.

Syscall convention (for ft_write / ft_read)

Almost the same, with two differences flagged in bold:

syscall number	rax
1st argument	rdi
2nd argument	rsi
3rd argument	rdx
4th argument	r10 (not rcx)
5th argument	r8
6th argument	r9
return value	rax

The instruction is syscall, and it destroys rcx and r11 — don't keep anything live in those across it.

Register preservation — who saves what

Class	Registers	Rule
Caller-saved (scratch)	rax, rcx, rdx, rsi, rdi, r8, r9, r10, r11	Use freely, no cleanup needed
Callee-saved	rbx, rbp, r12, r13, r14, r15	Must push at start, pop before ret if you touch them

The whole mandatory set fits inside the scratch registers, so you can usually avoid push/pop entirely.

Linux syscall numbers you'll need

Syscall	Number (rax)
read	0
write	1

On error, Linux returns a negative value in rax (e.g. -9), which you negate to get the errno value, store via __errno_location, and return -1.

Common instructions cheat sheet

Instruction	Effect
mov  dst, src	dst = src
xor  rax, rax	rax = 0 (idiomatic zeroing)
inc  / dec  reg	reg ± 1
add  / sub  a, b	a = a ± b
cmp  a, b	compare (sets flags, stores nothing)
je / jne	jump if equal / not equal
jl / jg	jump if signed less / greater
jmp  label	unconditional jump
call label	call a function
ret	return
push / pop reg	save / restore a register on the stack
