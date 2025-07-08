[bits 16]
[org 0x7C00]

STAGE2_OFFSET equ 0x0600        ; load stage2 low as hell

start:
    mov [BOOT_DRIVE], dl

    xor ax, ax
    mov ds, ax
    mov es, ax

    mov bx, STAGE2_OFFSET        ; destination = 0x0600
    mov dh, 1                    ; load 4 sectors for stage2 (adjust as needed)
    mov dl, [BOOT_DRIVE]
    call disk_load

    jmp 0x0000:STAGE2_OFFSET     ; jump to stage2

BOOT_DRIVE db 0

disk_load:
    pusha

    mov ah, 0x02              ; function 02h = read sectors
    mov al, dh                ; number of sectors to read
    mov ch, 0                 ; cylinder 0
    mov cl, 2                 ; sector 2 (bootloader = sector 1)
    mov dh, 0                 ; head 0
    mov dl, [BOOT_DRIVE]      ; drive number from BIOS
    int 0x13
    jc .error                 ; if carry set, fuck it

    ; show success
    mov ah, 0x0E
    mov al, '+'
    int 0x10
    jmp .done

.error:
    mov ah, 0x0E
    mov al, '!'
    int 0x10
    jmp $

.done:
    popa
    ret

times 510-($-$$) db 0
dw 0xAA55
