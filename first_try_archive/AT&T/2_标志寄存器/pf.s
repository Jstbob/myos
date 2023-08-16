.section .text
.global main
main:
    push %rbp
    mov %rsp, %rbp
    mov $0x3, %eax
    mov $0x1, %eax
    mov $0x1, %ebx
    add %ebx, %eax
    add $1, %eax
    pop %rbp  
    ret
