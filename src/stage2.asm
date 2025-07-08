[bits 16]
[org 0x0600]

KERNEL_OFFSET   equ 0x1000
KERNEL_SECTORS  equ 42

start:
    mov [BOOT_DRIVE], dl

    ; setup basic stack
    mov bp, 0x0700
    mov sp, bp

    xor ax, ax
    mov es, ax

    mov bx, KERNEL_OFFSET
    mov dh, KERNEL_SECTORS
    mov dl, [BOOT_DRIVE]
    call disk_load

    ; switch to protected mode
    call switch_to_32bit

BOOT_DRIVE db 0

.hang:
    jmp .hang

; ----------------------------------------
; DISK LOAD (no bullshit, simple version)
; ----------------------------------------
disk_load:
    pusha

    mov ah, 0x02              ; BIOS read
    mov al, dh                ; sectors to read
    mov ch, 0                 ; cylinder
    mov cl, 2                 ; sector 2 (start after stage1)
    mov dh, 0                 ; head
    mov dl, [BOOT_DRIVE]
    int 0x13
    jc .fail

    ; success marker
    mov ah, 0x0E
    mov al, '+'
    int 0x10
    jmp .done

.fail:
    mov ah, 0x0E
    mov al, '!'
    int 0x10
    jmp $

.done:
    popa
    ret

; ----------------------------------------
; GDT + PROTECTED MODE
; ----------------------------------------
switch_to_32bit:
    cli
    lgdt [gdt_descriptor]

    ; DEBUG: switch video mode to prove we're alive
    mov ax, 0x0012
    int 0x10

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp 0x08:protected_mode_start  ; far jump to code segment

; ----------------------------------------
; GDT STRUCTURE
; ----------------------------------------
gdt_start:
    dq 0x0000000000000000          ; null descriptor
    dq 0x00cf9a000000ffff          ; code segment
    dq 0x00cf92000000ffff          ; data segment
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10

; ----------------------------------------
; 32-BIT ENTRY
; ----------------------------------------
[bits 32]
protected_mode_start:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov ebp, 0x90000
    mov esp, ebp

    jmp BEGIN_32BIT

.loop:
    jmp .loop

BEGIN_32BIT:
    jmp 0x1200     ; kernel entry point
