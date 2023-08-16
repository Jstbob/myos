.section .data
arr:
    .byte 1,2,3,4,5,6 

 
.section .text
.global main
main:
    mov $arr, %edi    # 立即数赋值
    mov $9, %eax
    mov %eax, (%edi)
    mov %eax, 2(%edi)
    ret
