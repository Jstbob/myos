#include "idt.h"

.section .text
.global idt_flush
.global isr0
.global isr1
.global isr2
.global isr3
.global isr4
.global isr5
.global isr6
.global isr7
.global isr8
.global isr9
.global isr10
.global isr11
.global isr12
.global isr13
.global isr14
.global isr15
.global isr16
.global isr17
.global isr18
.global isr19
.global isr20
.global isr21
.global isr22
.global isr23
.global isr24
.global isr25
.global isr26
.global isr27
.global isr28
.global isr29
.global isr30
.global isr31
idt_flush:
    mov 4(%esp), %eax
    lidt (%eax)
    ret
isr0:
    cli
    push $0
    jmp handler 

isr1:
    cli
    push $1
    jmp handler 

isr2:
    cli
    push $2
    jmp handler 

isr3:
    cli
    push $3
    jmp handler 

isr4:
    cli
    push $4
    jmp handler 

isr5:
    cli
    push $5
    jmp handler 

isr6:
    cli
    push $6
    jmp handler 

isr7:
    cli
    push $7
    jmp handler 

isr8:
    cli
    push $8
    jmp handler 

isr9:
    cli
    push $9
    jmp handler 

isr10:
    cli
    push $10
    jmp handler 

isr11:
    cli
    push $11
    jmp handler 

isr12:
    cli
    push $12
    jmp handler 

isr13:
    cli
    push $13
    jmp handler 

isr14:
    cli
    push $14
    jmp handler 

isr15:
    cli
    push $15
    jmp handler 

isr16:
    cli
    push $16
    jmp handler 

isr17:
    cli
    push $17
    jmp handler 

isr18:
    cli
    push $18
    jmp handler 

isr19:
    cli
    push $19
    jmp handler 

isr20:
    cli
    push $20
    jmp handler 

isr21:
    cli
    push $21
    jmp handler 

isr22:
    cli
    push $22
    jmp handler 

isr23:
    cli
    push $23
    jmp handler 

isr24:
    cli
    push $24
    jmp handler 

isr25:
    cli
    push $25
    jmp handler 

isr26:
    cli
    push $26
    jmp handler 

isr27:
    cli
    push $27
    jmp handler 

isr28:
    cli
    push $28
    jmp handler 

isr29:
    cli
    push $29
    jmp handler 

isr30:
    cli
    push $30
    jmp handler 

isr31:
    cli
    push $31
    jmp handler

handler:
    call exception_handler
    add $4, %esp
    sti
    iret