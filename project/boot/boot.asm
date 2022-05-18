[org 0x7c00]
KERNEL_OFFSET equ 0x1000

    mov [BOOT_DRIVE], dl ; BIOS stores our boot drive in DL , so it ’s best to remember this for later.

    xor ax, ax                          
    mov es, ax
    mov ds, ax

    mov bp, 0x9000 ;set stack base
    mov sp, bp     ;set stack top

    

    call load_kernel

    call start_protected_mode 

    jmp $ ; hang

; include GDT
%include "boot/GDT.asm"

; include libs
%include "asmlibs/print.asm"
%include "asmlibs/disk.asm"
%include "asmlibs/ProtectedMode.asm"

[bits 16]
load_kernel:
    mov bx, KERNEL_OFFSET
    mov dh, 15
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_PROTECTED_MODE:
    call KERNEL_OFFSET

    jmp $ ; Hang



;global variables
BOOT_DRIVE: 
    db 0

;bootsector padding
times 510-($-$$) db 0
dw 0xaa55

