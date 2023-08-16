.section .data
arr:
    .byte 1,2,3,4,5,6 

 
.section .text
.global main
main:
    mov $2, %edi    # 立即数赋值
    mov $1, %edi
    mov $arr, %ebp
    mov -1(%ebp, %edi, 2), %eax
    ret
