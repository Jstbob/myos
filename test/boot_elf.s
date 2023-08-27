.section .multiboot
.align 4

header_start:
.long 0xE85250D6
.long 0
.long -(header_end - header_start + 0xE85250D6)
.long header_end - header_start
header_end:

.section .text
.global _start 
_start:
    movl $1, %eax
    movl $1, %ebx

loop:
    hlt
    jmp loop
