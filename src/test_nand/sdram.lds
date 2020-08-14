SECTIONS
{
    . = 0x00000000;

    __code_start = .;

    . = ALIGN(4);
    .text :
    {
        start.o(.text)
        *(.text*)
    }

    . = ALIGN(4);
    .rodata :
    {
        *(.rodata*)
    }

    . = ALIGN(4);
    .data :
    {
        *(.data*)
    }

    . = ALIGN(4);
    __bss_start = .;
    .bss :
    {
        *(.bss)
        *(.common)
    }
    _end = .;

}
