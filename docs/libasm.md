## Assembly guide
Explanation of x86-64 assembly.

## Contents

- [1. What is assembly?](#1-what-is-assembly)
- [2. Registers, Memory and Instructions](#2-registers-memory-and-instructions)
  - [Registers](#registers)
  - [Memory](#memory)
  - [Instructions](#instructions)
- [3. Flags and Jumps](#3-flags-and-jumps)
- [4. Calling Convention](#4-calling-convention)
- [5. Syscalls: talking to the Kernel](#5-syscalls-talking-to-the-kernel)

### 1. What is assembly?
Assembly language is a thin layer on top of machine code. Each assembly instruction corresponds (almost) one to one with a machine instruction.
example: C (source) -> assembly -> machine code (raw bytes the CPU runs)
A compiler like gcc turn C into assembly.

### 2. Registers, Memory and Instructions
#### Registers
A **register** is a tiny, fast storage slot living inside the CPU itself. A 64-bit CPU has a handful of general purpose 64bit registers. These are the variables of assembly.

**Most common ones:**  
A Markdown table would make this much cleaner:

| Register | Role | Argument |
| --- | --- | --- |
| `rax` | Value / accumulator | — |
| `rdi` | Function argument | 1st |
| `rsi` | Function argument | 2nd |
| `rdx` | Function argument | 3rd |
| `rcx` | Function argument | 4th |
| `r8` | Function argument | 5th |
| `r9` | Function argument | 6th |
| `rsp` | Stack pointer | — |
| `rbp` | Base pointer | — |

Each 64bit register can also be accessed in smaller pieces. This matters when working with single bytes like characters.  
Yep — for this, a simple table works nicely:

 | Register | Size | Refers to |
| --- | --- | --- |
| `rax` | 64-bit | Full register |
| `eax` | 32-bit | Low 32 bits of `rax` |
| `ax` | 16-bit | Low 16 bits of `rax` |
| `al` | 8-bit | Low 8 bits of `rax` (1 byte, e.g. a `char`) |

so al is the lowest bytes of rax. Writing to al changes just that byte.

#### Memory

Registers are few and small. Most data lives in memory (RAM).  
You access memory through an **address** (similar to a pointer in C).

In assembly, `[]` means **"the value stored at this address"** (dereference):

| Expression | Meaning |
|---|---|
| `rdi` | The address itself (the pointer) |
| `[rdi]` | The value stored at that address |
| `[rdi + rax]` | The value at address `rdi + rax` — like `ptr[i]` |
| `byte [rdi + rax]` | Treat the value at that address as a single byte |


### Instructions
An instruction is one operation:  
`opertation` `destination`, `source`

The result generally goes into the destination(left operand).  
 | Instruction | Meaning |
 | --- | --- |
| `mov rax, rdi` | copy rdi into rax |
| `xor rax, rax` | set rax to 0 (a fast, idiomatic "zero it") |
| `inc rax	rax` | = rax + 1 |
| `dec rax	rax` | = rax - 1 |
| `add rax, rdx` | rax = rax + rdx |
| `sub rax, rdx` | rax = rax - rdx |
| `cmp al, 0` | compare al with 0 (sets flags, stores nothing) |
| `ret` | return from the function |

### 3. Flags and Jumps
Assembly has no if, while or for. Instead it has **flags and jumps**.  
When running `cmp a, b`, the CPU substracts `b` from `a`, throws away the result, but records facts about that ressult in a special flags register.  
``(res = 0? = -1? = overflow? etc)``  

A conditional jump then reads those flags and decides whether to jump to a label. (a named position in code)  
`je	a == b` (jump if equal / result zero)  
`jne	a != b` (jump if not equal)  
`jl	a < b` (signed less-than)  
`jg	a > b` (signed greater-than)  
`jmp`	always (unconditional jump)  

A label is a name followed by a colon. Labels starting with . are local labels scoped to the curr function. (.loop, .done)
```
Example of while loop:
    xor rax, rax            ; i = 0
.loop:
    cmp byte [rdi + rax], 0 ; compare s[i] with '\0'
    je .done                ; if equal, exit the loop
    inc rax                 ; i++
    jmp .loop               ; go back and check again
.done:
    ret
```
### 4. Calling Convention
When on function calls another both must agree on where the args are and where the ret value goes.  
On 64bit Linux this agreement is the System V AMD64 calling convention.

The first six interger/pointer arguments come in registers, in this EXACT order:
rdi, rsi, rdx, rcx, r8, r9 (in a function with two params, rdi = 1st param, rsi = 2nd param)

For the return value, put the result in rax, then ret. size_t, ints, and pointers come back in rax/

registers split into two groups:
- Caller-saved (scratch): rax, rcx, rdx, rsi, rdi, r8, r9, r10, r11 (do not "survive")
- Callee-saved: rbx, rbp, r12, r13, r14, r15. If these are modified they MUST be restored to their original value before returning. (via push and pop)

### 5. Syscalls: talking to the Kernel
A syscall is a function call, but into the kernel. It has its own convention that is almost the same as the normal one with 2 differences:
1. put a syscall number in rax to say which kernel service is wanted.
2. the 4th argument uses r10 instead of rcx (syscall destroys rcx)

`rax` = syscall number  
`rdi, rsi, rdx, r10, r8, r9` = arguments  
`syscall`                     ; hand control to the kernel  
; result comes back in rax  

Linux specific: write is syscall number 1, read is 0. On error, the kernel returns a negative value in rax (ex: -9 means errno should be 9)

