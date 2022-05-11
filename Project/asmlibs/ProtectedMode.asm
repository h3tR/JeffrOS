[bits 16]
start_protected_mode:
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:initialize_protected_mode

[bits 32]
initialize_protected_mode:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000 ; set stack base
    mov esp, ebp     ; set stack top

    call BEGIN_PROTECTED_MODE