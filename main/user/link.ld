ENTRY(entry)

SECTIONS
{
    . = 0x800000000 ;

    .text :
    {
        *(.text)
    }

    .bss :
    {
        *(.bss)
    }

    .data :
    {
        *(.data .*data)
        *(.comment)
        *(.symtab)
    }
}
