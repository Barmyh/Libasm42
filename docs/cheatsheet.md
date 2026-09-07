## x86-64 Assembly Cheatsheet

## Contents

- [Registers](#registers)
- [Data size keywords](#data-size-keywords)
- [Calling convention (System V AMD64)](#calling-convention-system-v-amd64)
  - [Function arguments](#function-arguments--in-this-exact-order)
  - [Register preservation](#register-preservation)
- [Syscall convention](#syscall-convention)
  - [Common Linux syscall numbers](#common-linux-syscall-numbers)
- [Concrete examples](#concrete-examples)
  - [Data movement](#data-movement)
  - [Arithmetic & logic](#arithmetic--logic)
  - [Compare & branch](#compare--branch)
  - [Calls](#calls)
- [Memory addressing](#memory-addressing)
- [Quick Cheat Sheet](#quick-cheat-sheet)

### Registers

| 64-bit | 32-bit | 16-bit | 8-bit | Typical use                    |
|--------|--------|--------|-------|--------------------------------|
| `rax`  | `eax`  | `ax`   | `al`  | return value, syscall number   |
| `rbx`  | `ebx`  | `bx`   | `bl`  | callee-saved scratch           |
| `rdi`  | `edi`  | `di`   | `dil` | 1st arg                        |
| `rsi`  | `esi`  | `si`   | `sil` | 2nd arg                        |
| `rdx`  | `edx`  | `dx`   | `dl`  | 3rd arg                        |
| `rcx`  | `ecx`  | `cx`   | `cl`  | 4th arg / loop counter         |
| `r8`   | `r8d`  | `r8w`  | `r8b` | 5th arg                        |
| `r9`   | `r9d`  | `r9w`  | `r9b` | 6th arg                        |
| `rbp`  | `ebp`  | `bp`   | `bpl` | base/frame pointer             |
| `rsp`  | `esp`  | `sp`   | `spl` | stack pointer                  |
| `r10`–`r15` | `r10d`… | `r10w`… | `r10b`… | scratch / callee-saved |

**Rule of thumb:** writing to a 32-bit register (`eax`) zeroes the upper 32 bits
of the 64-bit register. Writing to 8- or 16-bit parts does *not* clear the rest.

---

### Data size keywords

Put these before a `[memory]` operand to say how many bytes to touch.

| Keyword | Bits | Bytes | C type          |
|---------|------|-------|-----------------|
| `byte`  | 8    | 1     | `char`          |
| `word`  | 16   | 2     | `short`         |
| `dword` | 32   | 4     | `int`           |
| `qword` | 64   | 8     | `long`, pointer |

```nasm
cmp byte  [rdi + rax], 0    ; read one char
mov dword [rax], ecx        ; store a 4-byte int (how to set errno)
```

---

## Calling convention (System V AMD64)

### Function arguments — in this exact order

| Arg | 1   | 2   | 3   | 4   | 5  | 6  |
|-----|-----|-----|-----|-----|----|----|
| Reg | rdi | rsi | rdx | rcx | r8 | r9 |

- **Return value → `rax`.**
- Arguments 7+ go on the stack

### Register preservation

| Class                  | Registers                                | Your responsibility          |
|------------------------|------------------------------------------|------------------------------|
| Caller-saved (scratch) | `rax rcx rdx rsi rdi r8 r9 r10 r11`      | Use freely, no cleanup       |
| Callee-saved           | `rbx rbp r12 r13 r14 r15`                | `push` before, `pop` after   |

---

## Syscall convention

Almost identical to the function convention, with **two differences**.

| Purpose        | Register           |
|----------------|--------------------|
| syscall number | **rax**            |
| arg 1          | rdi                |
| arg 2          | rsi                |
| arg 3          | rdx                |
| arg 4          | **r10**            |
| arg 5          | r8                 |
| arg 6          | r9                 |
| return value   | rax                |

- Instruction is `syscall`. It **destroys `rcx` and `r11`**.
- **Error signaling (Linux):** a **negative** return in `rax` means failure;
  the magnitude is the errno value (`-9` → errno `9`).

### Common Linux syscall numbers

| # | Name  | # | Name  |
|---|-------|---|-------|
| 0 | read  | 3 | close |
| 1 | write | 9 | mmap  |
| 2 | open  | 60| exit  |

---

## Concrete examples
### Data movement

| Instruction              | Effect                                        |
|--------------------------|-----------------------------------------------|
| `mov  dst, src`          | dst = src                                      |
| `movzx dst, src`         | move + zero-extend (unsigned byte → full reg)  |
| `movsx dst, src`         | move + sign-extend (signed widening)           |
| `lea  dst, [expr]`       | dst = the *address* expr (no memory read)      |
| `push reg` / `pop reg`   | save / restore on the stack                    |
| `xchg a, b`              | swap a and b                                   |

### Arithmetic & logic

| Instruction     | Effect                          |
|-----------------|---------------------------------|
| `add  a, b`     | a = a + b                       |
| `sub  a, b`     | a = a - b                       |
| `inc  / dec r`  | r ± 1                           |
| `neg  r`        | r = -r                          |
| `mul  / imul`   | unsigned / signed multiply      |
| `xor  a, a`     | a = 0 (idiomatic zeroing)       |
| `and / or / not`| bitwise ops                     |

### Compare & branch

| Instruction   | Effect / jumps if…                       |
|---------------|------------------------------------------|
| `cmp a, b`    | compare (sets flags, stores nothing)     |
| `test a, b`   | bitwise-AND flags (often `test r, r`)    |
| `je` / `jz`   | equal / zero                             |
| `jne` / `jnz` | not equal / not zero                     |
| `jl` / `jg`   | signed less / greater                    |
| `jle` / `jge` | signed ≤ / ≥                             |
| `jb` / `ja`   | unsigned below / above                   |
| `js` / `jns`  | sign set / not set (negative / positive) |
| `jmp label`   | unconditional jump                       |

### Calls

| Instruction              | Effect                                 |
|--------------------------|----------------------------------------|
| `call label`             | call a function                        |
| `call func wrt ..plt`    | call an **external** function (PIE)    |
| `syscall`                | enter the kernel                       |
| `ret`                    | return to caller                       |

---

## Memory addressing

Square brackets mean "the value at this address."

```nasm
[rdi]                ; value at address in rdi (dereference a pointer)
[rdi + rax]          ; value at rdi + rax        → like ptr[i]
[rdi + rax*4]        ; scaled: rdi + rax*4       → like int_array[i]
[rdi + rax*4 + 8]    ; base + index*scale + displacement
byte [rdi + rax]     ; the single byte at that address
```

---


## Quick Cheat Sheet

```
ARGS IN:      rdi rsi rdx rcx r8 r9        (4th syscall arg = r10)
RETURN:       rax
SYSCALL #:    rax   → 0 read, 1 write
SCRATCH:      rax rcx rdx rsi rdi r8 r9 r10 r11
PRESERVE:     rbx rbp r12 r13 r14 r15
EXTERNAL CALL: call name wrt ..plt
ERRNO:        neg → push → call __errno_location wrt ..plt → pop → mov dword → -1
ALIGN:        rsp must be 16-byte aligned at every call
[rdi+rax]  = ptr[i]      byte [rdi+rax] = one char
xor r,r    = zero it     movzx = unsigned widen
cmp a,b then je/jne/jl/jg to branch
```