disk_load:
    pusha

    xor si, si                ; si = sectors loaded

.load_next:
    cmp si, dx                ; dx = total sectors
    jge .done                 ; done

    ; how much room in current segment?
    mov ax, 0xFFFF
    sub ax, bx
    shr ax, 9                 ; how many 512-byte sectors can fit?
    cmp ax, 0
    je .bump_segment

    mov cx, dx
    sub cx, si
    cmp cx, ax
    jbe .set_chunk
    mov cx, ax                ; fit only what's possible
.set_chunk:

    push cx

    ; DEBUG indicator
    mov ah, 0x0E
    mov al, '.'
    int 0x10

    ; BIOS read
    mov ah, 0x02
    mov al, cl
    mov ch, 0
    mov cl, 2
    mov dh, 0
    ; dl = drive
    int 0x13
    jc disk_error

    ; DEBUG success
    mov ah, 0x0E
    mov al, '+'
    int 0x10

    pop cx
    add si, cx                ; sectors read

    ; bump bx
    mov ax, cx
    shl ax, 9
    add bx, ax
    jnc .load_next

.bump_segment:
    ; segment wraparound: calculate segment bump and offset
    mov ax, cx
    shl ax, 9                 ; bytes = sectors * 512
    mov dx, ax               ; keep copy

    shr ax, 4                 ; convert to paragraphs
    push ax
    mov ax, es
    add ax, [esp]             ; es += ax
    mov es, ax
    pop ax

    and dx, 0xF               ; leftover byte offset
    mov bx, dx

    jmp .load_next

.done:
    popa
    ret

disk_error:
    mov ah, 0x0E
    mov al, '!'
    int 0x10
    jmp $
