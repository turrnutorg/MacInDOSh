ENTRY(_start)

SECTIONS {
    . = 0x1000;  /* tell the linker: this is where we're putting the code */

    .text : {
        *(.text.start)     /* where _start lives */
        KEEP(*(.main))     /* where your cursed main is */
        *(.text*)
        *(.rodata*)
    }

    .data ALIGN(4K) : { *(.data*) }

    .bss ALIGN(4K) (NOLOAD) : {
        _bss_start = .;
        *(COMMON)
        *(.bss*)
        _bss_end = .;
    }

    .stack ALIGN(4K) (NOLOAD) : {
        stack_bottom = .;
        . += 8192;
        stack_top = .;
    }

    .heap ALIGN(4K) (NOLOAD) : {
        __heap_start = .;
        . += 0x100000;
        __heap_end = .;
    }

    /DISCARD/ : {
        *(.eh_frame*)
        *(.comment)
        *(.note*)
        *(.fini_array*)
        *(.init_array*)
    }
}
