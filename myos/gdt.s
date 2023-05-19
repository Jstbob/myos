#include "gdt.h"

.section .text
.global gdt_flush
gdt_flush:
    mov 4(%esp), %eax
    lgdt (%eax)
    ljmp $0x08, $flush_cs      # flsuh cs
flush_cs: 
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss 
    ret
