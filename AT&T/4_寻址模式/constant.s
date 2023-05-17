.section .rodata
constant:
    .int 0x12345678

.section .text
.global main
main:
    ret

print:
    push %ebp
    mov %esp, %ebp
    
    pop %ebp
    ret