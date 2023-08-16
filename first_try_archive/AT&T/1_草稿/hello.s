# hello.s
.section .data
str:
    .string "hello\n"

.section .text
.globl main
.type main, @function
main:
    pushq %rbp
    movq %rsp, %rbp
    leaq str(%rip), %rax
    movq %rax, %rdi
    movl $0, %eax
    call printf
    popq %rbp
    ret
