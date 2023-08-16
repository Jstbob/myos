.section .data
msg:
    .string "helloworld\n"

.section .text
.global main
main:
    mov $4, %eax
    mov $1, %ebx        # file descriptor (stdout)
    mov $msg, %ecx
    mov $11, %edx
    int $0x80
    ret
