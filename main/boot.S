#include "boot.h"

# qemu支持直接引导multiboot1，不支持multiboot2
# 这里使用multiboot1 spec的约定
# spec还约定了机器的寄存器状态，重点要注意的是esp、gdtr此时还没有定义
# 设置flags[0]，以得到内存大小信息
.set MAGIC, 0x1BADB002
.set FLAGS, 1
.set CHECKSUM, - (MAGIC + FLAGS)

.section .multiboot
.align(4)
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .text
.global boot
.extern kmain
.extern kernel_pd
.extern kernel_pt
.extern pdbr
boot:
    cli
    movl $stack_end, %esp
    # 传给kmain引导信息
    pushl %ebx
    
    # 设置gdt表
    lgdt gdtr   # debug，会在这里重置EIP
    # 使用段选择子初始化段寄存器
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %ss
    mov $0, %ax
    mov %ax, %fs
    mov %ax, %gs
    ljmp $0x08, $flush_cs

flush_cs:
    # 设置分页，这里只做32MB内核内存的映射，每个目录可以映射1MB物理地址，使用8个目录即可
    movl $0, %eax
    movl $kernel_pt, %ebx
    orl $PAGE_ATTR, %ebx
    movl $kernel_pd, %edi
set_pd:
    movl %ebx, (%edi,%eax,4)
    addl $4096, %ebx
    inc %eax
    cmp $PD_COUNT, %eax
    jne set_pd

    movl $0, %eax
    movl $0, %ebx
    orl $PAGE_ATTR, %ebx
    movl $kernel_pt, %edi
set_pt:
    movl %ebx, (%edi,%eax,4)
    addl $4096, %ebx
    inc %eax
    cmpl $KERNEL_PAGE_ENTRIES, %eax
    jne set_pt

    movl $kernel_pd, %eax
    movl %eax, %cr3
    # 开启分页，使能PG、WP位
    movl %cr0, %eax
    orl $0x80000001, %eax
    # -bug: 设置cr0后，内存内容消失，页面和目录必须填充满才有效
    movl %eax, %cr0     

    call kmain  # 进入内核
rep:
    hlt
    jmp rep

.align(8)
gdt:
    .quad NULL_SEG
    .quad KCODE_SEG
    .quad KDATA_SEG
    .quad UCODE_SEG
    .quad UDATA_SEG

.align(4)
gdtr:
    .word (gdtr - gdt -1)      # 5*8-1
    .long gdt

.section .stack
stack_head:
.skip (1024 * 1024 * 4) # 可用栈大小为4MB
stack_end:
