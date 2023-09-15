.section .text
.global add

add:
    push %ebp
    mov %esp, %ebp
    push %ebx
    mov 8(%ebp), %eax
    mov 12(%ebp), %ebx
    add %ebx, %eax
    pop %ebx
    mov %ebp, %esp
    pop %ebp
    ret


// .section .text
// .global add

// add:
//     pushl	%ebp
//     movl	%esp, %ebp
//     movl	8(%ebp), %edx
//     movl	12(%ebp), %eax
// 	   addl	%edx, %eax
// 	   popl	%ebp
//     ret
