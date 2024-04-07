ENTRY(_entry)

SECTIONS
{
    . = 1M;

    .multiboot2 :
    {
        *(.multiboot2)
    }

    .text :
    {
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