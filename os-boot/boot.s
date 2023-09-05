/*
    @todo
    1. Undertard first section.
    2. Make img, boot into 16bit model.
*/

// 0x7c00
.section .text
.code16
start:
    cli
    
    mov $0x20, %ax         // kernel data
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %ss
    mov $0, %ax
    mov %ax, %fs
    mov %ax, %gs
    lgdt gdtrd

// set PE bit, turn on page
    mov %cr0, %eax
    or $1, %eax
    mov %eax, %cr0 
    jmp protect_mode

.code32
protect_mode:
    mov start, %esp
    call _entry
loop:
    hlt
    jmp loop

gdt:
    .quad 0
    .quad 0xffff000000fbcf0f    // user code    0x0008
    .quad 0xffff000000f3cf0f    // user data    0x0010
    .quad 0xffff0000009bcf0f    // kernel code  0x0018
    .quad 0xffff00000093cf0f    // kernel data  0x0020

gdtrd:
    .word (gdtrd - gdt -1)      // 5*8-1
    .long gdt

start_end:

.fill 510 - (start_end - start), 1, 0
.byte 0x55, 0xAA
