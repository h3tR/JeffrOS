; requires an include of the print.asm library
disk_load:
    push dx

    mov ah, 0x02
    mov al, dh
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02

    int 0x13

    jc disk_error
    pop dx
    ret


disk_error:
    mov bx, DISK_ERROR_MSG
    call print_stringrm
    jmp $

DISK_ERROR_MSG:
    db "Disk read error!",0