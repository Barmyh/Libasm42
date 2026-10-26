extern __errno_location
extern malloc


section .text
global ft_calloc

ft_calloc:
        push rbx

        mov rbx, rsi            ; save size

        ; Check multiplication overflow
        test rbx, rbx
        jz .zero_size

        mov rax, -1             ; SIZE_MAX
        xor edx, edx
        div rbx                 ; SIZE_MAX / size

        cmp rdi, rax            ; nmemb > SIZE_MAX / size?
        ja .error

        ; Calculate total size
        mov rax, rdi            ; nmemb
        imul rax, rsi           ; total = nmemb * size

        ; Allocate memory
        mov rdi, rax
        push rax                ; save total size
        call malloc
        pop rcx                 ; rcx = total size

        test rax, rax
        jz .error

        ; Zero the allocated memory
        mov rdi, rax            ; destination pointer
        xor edx, edx            ; zero value

.zero_loop:
        test rcx, rcx
        jz .zero_done

        mov byte [rdi], dl      ; write zero byte
        inc rdi                 ; next byte
        dec rcx                 ; remaining bytes
        jmp .zero_loop

.zero_done:
        ; Return allocated pointer
        ; rax still holds the original pointer
        pop rbx
        ret

.zero_size:
        xor edi, edi            ; malloc(0)
        call malloc
        pop rbx
        ret

.error:
        xor eax, eax            ; return NULL
        pop rbx
        ret


; void *ft_calloc(size_t count, size_t size)
; allocates mem for an array of n elements of size bytes.
; returns a pointer to the allocated memory
; memory is set to 0
