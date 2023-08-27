ENTRY(_start)

SECTIONS
{
    .text 0x100000 :
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
    }
}
