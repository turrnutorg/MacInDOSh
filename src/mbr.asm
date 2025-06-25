[bits 16]
[org 0x7c00]

KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl

mov bp, 0x9000
mov sp, bp

mov ax, 0x000F
int 0x10

mov bx, KERNEL_OFFSET
mov dh, 51
mov dl, [BOOT_DRIVE]
call disk_load

call switch_to_32bit

jmp $

; your includes
%include "disk.asm"
%include "gdt.asm"
%include "switch-to-32bit.asm"

[bits 32]
BEGIN_32BIT:
    call KERNEL_OFFSET
    jmp $

BOOT_DRIVE db 0
times 510-($-$$) db 0
dw 0xaa55
