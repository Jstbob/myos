.section .data      # init var
var1:
    .long 0x12345678

.section .bss       # unint var
var2:
    .fill 4

.section .text
.global main
main:
    mov var1, %eax
    mov var2, %eax
    ret