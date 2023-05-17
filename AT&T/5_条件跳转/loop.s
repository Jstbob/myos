.section .text
.global main
main:
    mov $3, %ecx
label:
    dec %ecx
    loop label
    ret
