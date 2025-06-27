; mouse.asm – ps/2 driver, one and only copy
[bits 32]

%define PORT_DATA   0x60
%define PORT_STAT   0x64
%define PORT_CMD    0x64
%define KERNEL_DS   0x10     ; gdt data selector

section .bss
mouse_packet   resb 3
packet_ready   resb 1
byte_count     resb 1

section .text
global mouse_init
global mouse_irq_handler
global mouse_get_packet
global packet_ready
global mouse_packet


extern pic_send_eoi

; ------------------------------------------------------------
mouse_wait_read:
    in  al, PORT_STAT
    test al, 1
    jz  mouse_wait_read
    ret

mouse_wait_write:
    in  al, PORT_STAT
    test al, 2
    jnz mouse_wait_write
    ret

; al = command byte
mouse_write_device:
    push eax
    mov  bl, al
    call mouse_wait_write
    mov  al, 0xD4
    out  PORT_CMD, al
    call mouse_wait_write
    mov  al, bl
    out  PORT_DATA, al
    pop  eax
    ret

; ------------------------------------------------------------
mouse_init:
    call mouse_wait_write
    mov  al, 0xA8
    out  PORT_CMD, al

    call mouse_wait_write
    mov  al, 0x20
    out  PORT_CMD, al
    call mouse_wait_read
    in   al, PORT_DATA
    or   al, 0x02
    mov  bl, al

    call mouse_wait_write
    mov  al, 0x60
    out  PORT_CMD, al
    call mouse_wait_write
    mov  al, bl
    out  PORT_DATA, al

    mov  al, 0xF6
    call mouse_write_device
    call mouse_wait_read
    in   al, PORT_DATA

    mov  al, 0xF4
    call mouse_write_device
    call mouse_wait_read
    in   al, PORT_DATA

    mov byte [byte_count],   0
    mov byte [packet_ready], 0
    ret

; ------------------------------------------------------------
mouse_irq_handler:
    mov byte [0xA0000], 0xFF
    pusha
    push ds
    push es

    mov  ax, KERNEL_DS
    mov  ds, ax
    mov  es, ax

    in   al, PORT_DATA

    cmp  byte [byte_count], 0
    jne  .continue
    test al, 0x08
    jz   .eoi

.continue:
    mov bl, [byte_count]
    cmp bl, 0
    je  .byte0
    cmp bl, 1
    je  .byte1

    mov [mouse_packet+2], al
    mov byte [byte_count], 0
    mov byte [packet_ready], 1
    jmp .eoi

.byte0:
    mov [mouse_packet], al
    inc byte [byte_count]
    jmp .eoi
.byte1:
    mov [mouse_packet+1], al
    inc byte [byte_count]

.eoi:
    pop es
    pop ds
    popa
    call pic_send_eoi
    iretd

; ------------------------------------------------------------
; int mouse_get_packet(&b0,&b1,&b2)
mouse_get_packet:
    mov al, [packet_ready]
    test al, al
    jz  .none

    mov byte [packet_ready], 0

    mov esi, [esp+4]
    mov edi, [esp+8]
    mov ebx, [esp+12]

    mov al, [mouse_packet]
    mov [esi], al
    mov al, [mouse_packet+1]
    mov [edi], al
    mov al, [mouse_packet+2]
    mov [ebx], al

    mov eax, 1
    ret
.none:
    xor eax, eax
    ret
