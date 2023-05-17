.section .text
.global _asm_set_pos
_asm_set_pos:
    push %ebp
    mov %esp, %ebp
    mov $14, %eax
    out %al, $0x3D4
    mov 1(%ebp), %eax
    out %al, $0x3D5
    mov $15, %eax
    out %al, $0x3D4
    mov (%ebp), %eax
    out %al, $0x3D5
    pop %ebp
    ret
