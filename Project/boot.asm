
[org 0x7c00]
    mov [BOOT_DRIVE], dl

    mov bp, 0x8000 ;set stack base
    mov sp, bp     ;set stack top

    ;load 5 sectors (0x0000:0x9000; ES:BX) from boot disk
    mov bx, 0x9000 
    mov dh,5
    mov dl, [BOOT_DRIVE]
    call disk_load

    ;print first loaded word (0xdada)
    mov dx, [0x9000]
    call print_hexadecimal

    ;print first word from second sector (0xface)
    mov dx, [0x9000 + 512]
    call print_hexadecimal

    jmp $ 

; include libs
%include "print.asm"
%include "disk.asm"


;global variables
BOOT_DRIVE:
    db 0

;bootsector padding
times 510-($-$$) db 0
dw 0xaa55

;disk sector indicators
times 256 dw 0xdada
times 256 dw 0xface