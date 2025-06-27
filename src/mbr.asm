[bits 16]
[org 0x7C00]

KERNEL_OFFSET equ 0x8000

mov [BOOT_DRIVE], dl         ; save boot drive

mov bp, 0x1000               ; setup stack
mov sp, bp

mov ax, 0x0000               ; set ES to 0
mov es, ax

mov bx, KERNEL_OFFSET        ; load kernel to 0x8000
mov dh, 54
mov dl, [BOOT_DRIVE]         ; boot drive
call disk_load

mov ax, 0x0012
int 0x10

call switch_to_32bit

jmp $

; ==== Includes ====
%include "disk.asm"
%include "gdt.asm"
%include "switch-to-32bit.asm"

[bits 32]
BEGIN_32BIT:
    jmp 0x8000


BOOT_DRIVE db 0

times 510-($-$$) db 0
dw 0xAA55
