.section .text
.global main
main:
    push %rbp
    mov %rsp, %rbp
    mov $0x7fffffff, %eax
    mov $0x7fffffff, %ebx
    add %ebx, %eax
    pop %rbp  
    ret
