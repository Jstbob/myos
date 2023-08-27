ENTRY(multiboot_entry)

SECTIONS
{
    . = 1M;

    .text :
    {
        *(.text)
    }

    _end = .;
}