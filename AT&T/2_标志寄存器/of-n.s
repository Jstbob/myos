.section .text
.global main
main:
    push %rbp
    mov %rsp, %rbp
    mov $0xffffffff, %eax
    mov $0x00000001, %ebx
    add %ebx, %eax
    pop %rbp  
    ret
