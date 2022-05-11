[org 0x7c00]

    mov bp, 0x8000 ;set stack base
    mov sp, bp     ;set stack top

    call start_protected_mode 

    jmp $ 

; include GDT
%include "GDT.asm"

; include libs
%include "asmlibs/print.asm"
%include "asmlibs/ProtectedMode.asm"

[bits 32]
BEGIN_PROTECTED_MODE:

    mov ebx, MSG_PROT_MODE
    call print_string
    jmp $ ; Hang

MSG_PROT_MODE:
     db " Successfully landed in 32 - bit Protected Mode " , 0


;bootsector padding
times 510-($-$$) db 0
dw 0xaa55

