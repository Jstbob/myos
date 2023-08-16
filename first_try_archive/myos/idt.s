#include "descriptor_tables.h"

.section .text
.extern idt_tables
.global isr_common_stub
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
.global irq0
.global irq1
.global irq2
.global irq3
.global irq4
.global irq5
.global irq6
.global irq7
.global irq8
.global irq9
.global irq10
.global irq11
.global irq12
.global irq13
.global irq14
.global irq15
isr0:
    cli
    push $0
    jmp isr_common_stub
            
isr1:
    cli
    push $1
    jmp isr_common_stub
            
isr2:
    cli
    push $2
    jmp isr_common_stub
            
isr3:
    cli
    push $3
    jmp isr_common_stub
            
isr4:
    cli
    push $4
    jmp isr_common_stub
            
isr5:
    cli
    push $5
    jmp isr_common_stub
            
isr6:
    cli
    push $6
    jmp isr_common_stub
            
isr7:
    cli
    push $7
    jmp isr_common_stub
            
isr8:
    cli
    push $8
    jmp isr_common_stub
            
isr9:
    cli
    push $9
    jmp isr_common_stub
            
isr10:
    cli
    push $10
    jmp isr_common_stub
            
isr11:
    cli
    push $11
    jmp isr_common_stub
            
isr12:
    cli
    push $12
    jmp isr_common_stub
            
isr13:
    cli
    push $13
    jmp isr_common_stub
            
isr14:
    cli
    push $14
    jmp isr_common_stub
            
isr15:
    cli
    push $15
    jmp isr_common_stub
            
isr16:
    cli
    push $16
    jmp isr_common_stub
            
isr17:
    cli
    push $17
    jmp isr_common_stub
            
isr18:
    cli
    push $18
    jmp isr_common_stub
            
isr19:
    cli
    push $19
    jmp isr_common_stub
            
isr20:
    cli
    push $20
    jmp isr_common_stub
            
isr21:
    cli
    push $21
    jmp isr_common_stub
            
isr22:
    cli
    push $22
    jmp isr_common_stub
            
isr23:
    cli
    push $23
    jmp isr_common_stub
            
isr24:
    cli
    push $24
    jmp isr_common_stub
            
isr25:
    cli
    push $25
    jmp isr_common_stub
            
isr26:
    cli
    push $26
    jmp isr_common_stub
            
isr27:
    cli
    push $27
    jmp isr_common_stub
            
isr28:
    cli
    push $28
    jmp isr_common_stub
            
isr29:
    cli
    push $29
    jmp isr_common_stub
            
isr30:
    cli
    push $30
    jmp isr_common_stub
            
isr31:
    cli
    push $31
    jmp isr_common_stub

isr_common_stub:
    pusha
    
    mov %ds, %ax
    push %eax

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    
    call idt_disatch

    pop %eax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    popa
    add $4, %esp
    sti
    iret

irq0:
    cli
    push $32
    jmp isr_common_stub
            
irq1:
    cli
    push $33
    jmp isr_common_stub
            
irq2:
    cli
    push $34
    jmp isr_common_stub
            
irq3:
    cli
    push $35
    jmp isr_common_stub
            
irq4:
    cli
    push $36
    jmp isr_common_stub
            
irq5:
    cli
    push $37
    jmp isr_common_stub
            
irq6:
    cli
    push $38
    jmp isr_common_stub
            
irq7:
    cli
    push $39
    jmp isr_common_stub
            
irq8:
    cli
    push $40
    jmp isr_common_stub
            
irq9:
    cli
    push $41
    jmp isr_common_stub
            
irq10:
    cli
    push $42
    jmp isr_common_stub
            
irq11:
    cli
    push $43
    jmp isr_common_stub
            
irq12:
    cli
    push $44
    jmp isr_common_stub
            
irq13:
    cli
    push $45
    jmp isr_common_stub
            
irq14:
    cli
    push $46
    jmp isr_common_stub
            
irq15:
    cli
    push $47
    jmp isr_common_stub
