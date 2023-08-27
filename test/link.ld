ENTRY(_start)

SECTIONS
{
    . = 1M;
	phys = .;

    .text :
    {
        *(.boot)
        *(.text)
    }

    .data :
    {
        *(.data)
    }

    bss_start = .;
    .bss :
    {
        *(COMMON)
        *(.bss)
        *(.stack)
    }

    _end = .;
}