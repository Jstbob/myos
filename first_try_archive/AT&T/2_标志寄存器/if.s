.section .text
.global main
main:
    push %rbp
    mov %rsp, %rbp
    cli
    sti
    pop %rbp
    ret
