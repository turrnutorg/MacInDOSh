section .text.start
[bits 32]
global _start
extern main

_start:
    call main
    jmp $
