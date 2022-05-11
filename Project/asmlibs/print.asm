[bits 32]

;define constants
VMEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

; prints string from EDX
print_string:
    pusha
    mov edx, VMEMORY

.print_char:
    mov al, [ebx] ; store char in al
    mov ah, WHITE_ON_BLACK ; set colors

    cmp al, 0 ; check for string terminator
    je .end

    mov [edx], ax ; store char + colors to current char cell

    inc ebx ; next char
    add edx, 2 ; next char cell

    jmp .print_char

.end:
    popa
    ret


