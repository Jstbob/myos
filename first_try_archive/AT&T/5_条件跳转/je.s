.section .text
.global main
main:
    mov $1, %rcx
    cmp $1, %rcx
    je label1
    mov $1, %rbx 
label1:
    cmp $0, %rcx
    jl label2
    mov $2, %rbx 
label2:
    cmp $1, %rcx
    jle label3
    mov $3, %rbx 
label3:
    cmp $2, %rcx 
    jge label4
    mov $4, %rbx 
label4:
    cmp $1, %rcx
    jg label3
    mov $5, %rbx 
    ret
