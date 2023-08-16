.section .rodata
.LC0:
	.string	"%d"
.STR:
    .string "helloworld"

.section .text
.globl	main
.type	main, @function
main:
    endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$666, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	popq	%rbp
	ret
	
# |__ Flag
# 	|__ EF
#	|__ CF
#	|__ EF
#	|__ OF
