#include "descriptor_tables.h"

.section .text
.global gdt_flush
.global idt_flush
gdt_flush:
    mov 4(%esp), %eax 
    lgdt (%eax)
    mov $0x10, %ax 
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    jmp flush
flush:
    ret

idt_flush:
    mov 4(%esp), %eax 
    lidt (%eax)
    ret
