.section .data
arr:
    .byte 1,2,3,4,5,6 

.section .text
.global main
main:
    mov $2, %ebx    # 立即数赋值
    mov $arr, %ebp
    mov -1(%ebp, %ebx, 2), %eax
    ret
