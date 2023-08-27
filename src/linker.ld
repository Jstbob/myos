ENTRY(_entry)

SECTIONS
{
    . = 1M;

    .text :
    {
        *(.multiboot)
        *(.text)
    }

    .data :
    {
        *(.data)
    }

    .rodata :
    {
        *(.rodata)
    }

    .bss :
    {
        *(COMMON)
        *(.bss)
        *(.stack)
    }
}