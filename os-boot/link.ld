ENTRY(start)

SECTIONS
{
    // 1GB kernel, 1-4GB user.
    . = 0x1001000000;

    .text :
    {
        *(.text)
    }
}

