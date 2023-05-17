.section .text
.global main
main:
    push %ebp
    mov %esp, %ebp
    mov $9, %al
    add $1, %al
    daa
    pop %ebp  
    ret
