# fist_asm.s
.section .text
.globl _entry
.type _entry, @function
_entry:
    movl $2, %eax
    ret
