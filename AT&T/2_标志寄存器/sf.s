.section .text
.global main
main:
    push %rbp
    mov %rsp, %rbp
    mov $0, %eax   # eax = 0
    sub $1, %eax
    add $1, %eax
    pop %rbp
    ret
