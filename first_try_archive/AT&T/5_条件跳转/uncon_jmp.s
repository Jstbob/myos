.section .text
.global main
main:
    mov $1, %eax
    jmp label
    mov $2, %eax
label:    
    mov $6, %ebx
    ret
