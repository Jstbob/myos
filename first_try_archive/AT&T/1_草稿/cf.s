.section .text
.global main
main:
	movl $0xFFFFFFFE, %eax
	movl $1, %ebx
	add %eax, %ebx
	ret
