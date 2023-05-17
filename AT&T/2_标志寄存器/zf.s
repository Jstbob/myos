.section .text
.global main
main:
    push %rbp
    mov %rsp, %rbp
    mov $1, %rax
    sub $1, %rax
    add $1, %rax
    pop %rbp
    ret
