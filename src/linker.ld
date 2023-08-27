ENTRY(entry)

SECTIONS
{
    . = 1M;
    load_address = .;

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

    bss_start = .;
    .bss :
    {
        *(.bss)
    }
    bss_end_addr = .;

    load_end_addr = .;
}