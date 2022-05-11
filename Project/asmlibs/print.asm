;prints bx as a string
print_string:
    push al
    int 0x10 
    inc bx
    mov al, [bx] ;set al to the next value
    cmp al, 0x00 ;if the current value is null terminate the loop, pop and return
    je .exit 
    jmp print_string
.exit:
    pop al
    ret

;prints dx as hex
print_hexadecimal:
    push ax
    mov bx, HEX_OUT+5
    mov ax, 0x000f
    and ax, dx
    cmp ax, 0x000a
    jl .num
    jmp .alpha

.num:
    add ax, 0x0030
    jmp .next

.alpha:
    add ax, 0x0037
    jmp .next

.next:
    mov [bx], dx
    dec bx
    shr ax, 4
    cmp ax, 0x0000
    jne print_hexadecimal
    jmp .out

.out:
    mov bx, HEX_OUT ;pass HEX_OUT as an argument to the print_string function
    call print_string
    pop ax
    ret

;global variables
HEX_OUT: db '0x0000',0