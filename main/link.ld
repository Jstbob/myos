ENTRY(boot)

SECTIONS
{
    . = 1M;    # bios占用区

    .text : ALIGN(4096)
    {
        *(.multiboot)
        *(.text)
    }

    .bss : ALIGN(4096)
    {
        # .stack区紧跟在.text区后，越界就会发生写入错误
        *(.stack)
        *(.bss)     
    }

    .data : ALIGN(4096)
    {
        *(.data)
    }

    _end = (. + 4096) & 4096;    # 内核映像4k对齐
    # _end之后的区域为可用区域
    # 人为约定内核区域为32MB，0-32MB逻辑地址映射到0-32MB的物理地址，2GB以上映射到32MB - PHY_MAX。
}
