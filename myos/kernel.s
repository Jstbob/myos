	.file	"kernel.c"
	.text
	.globl	buff
	.section	.rodata
	.align 4
	.type	buff, @object
	.size	buff, 4
buff:
	.long	753664
	.globl	WIDE
	.align 2
	.type	WIDE, @object
	.size	WIDE, 2
WIDE:
	.value	80
	.globl	HEIHT
	.align 2
	.type	HEIHT, @object
	.size	HEIHT, 2
HEIHT:
	.value	25
	.globl	cur_x
	.bss
	.align 2
	.type	cur_x, @object
	.size	cur_x, 2
cur_x:
	.zero	2
	.globl	cur_y
	.align 2
	.type	cur_y, @object
	.size	cur_y, 2
cur_y:
	.zero	2
	.globl	DISPLAY_MODE
	.data
	.type	DISPLAY_MODE, @object
	.size	DISPLAY_MODE, 1
DISPLAY_MODE:
	.byte	15
	.text
	.globl	to_char16
	.type	to_char16, @function
to_char16:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	8(%ebp), %edx
	movb	%dl, -4(%ebp)
	movzbl	DISPLAY_MODE@GOTOFF(%eax), %eax
	movzbl	%al, %eax
	sall	$8, %eax
	movl	%eax, %edx
	movsbw	-4(%ebp), %ax
	orl	%edx, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	to_char16, .-to_char16
	.globl	set_pos
	.type	set_pos, @function
set_pos:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.dx
	addl	$_GLOBAL_OFFSET_TABLE_, %edx
	movl	8(%ebp), %ecx
	movl	12(%ebp), %eax
	movw	%cx, -12(%ebp)
	movw	%ax, -16(%ebp)
	movw	$0, cur_x@GOTOFF(%edx)
	movw	$0, cur_y@GOTOFF(%edx)
	movzwl	-16(%ebp), %ecx
	movl	%ecx, %eax
	sall	$2, %eax
	addl	%ecx, %eax
	sall	$4, %eax
	movl	%eax, %ecx
	movzwl	-12(%ebp), %eax
	addl	%ecx, %eax
	movzwl	%ax, %eax
	subl	$12, %esp
	pushl	%eax
	movl	%edx, %ebx
	call	asm_set_pos@PLT
	addl	$16, %esp
	nop
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	set_pos, .-set_pos
	.globl	screen_putc
	.type	screen_putc, @function
screen_putc:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$36, %esp
	.cfi_offset 3, -12
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	8(%ebp), %ecx
	movl	12(%ebp), %edx
	movl	16(%ebp), %eax
	movw	%cx, -28(%ebp)
	movw	%dx, -32(%ebp)
	movb	%al, -36(%ebp)
	movzwl	-32(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	movl	%eax, %edx
	movzwl	-28(%ebp), %eax
	addl	%edx, %eax
	movw	%ax, -10(%ebp)
	movsbl	-36(%ebp), %eax
	movl	$753664, %ecx
	movzwl	-10(%ebp), %edx
	addl	%edx, %edx
	leal	(%ecx,%edx), %ebx
	pushl	%eax
	call	to_char16
	addl	$4, %esp
	movw	%ax, (%ebx)
	addw	$1, -28(%ebp)
	movl	$80, %eax
	cmpw	-28(%ebp), %ax
	jnb	.L5
	addw	$1, -32(%ebp)
	movl	$80, %eax
	subw	%ax, -28(%ebp)
.L5:
	addw	$1, -32(%ebp)
	movzwl	-32(%ebp), %edx
	movzwl	-28(%ebp), %eax
	subl	$8, %esp
	pushl	%edx
	pushl	%eax
	call	set_pos
	addl	$16, %esp
	nop
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	screen_putc, .-screen_putc
	.globl	screen_clear
	.type	screen_clear, @function
screen_clear:
.LFB3:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movw	$0, -10(%ebp)
	jmp	.L7
.L10:
	movw	$0, -12(%ebp)
	jmp	.L8
.L9:
	movzwl	-10(%ebp), %edx
	movzwl	-12(%ebp), %eax
	subl	$4, %esp
	pushl	$0
	pushl	%edx
	pushl	%eax
	call	screen_putc
	addl	$16, %esp
	addw	$1, -12(%ebp)
.L8:
	cmpw	$79, -12(%ebp)
	jbe	.L9
	addw	$1, -10(%ebp)
.L7:
	cmpw	$24, -10(%ebp)
	jbe	.L10
	subl	$8, %esp
	pushl	$0
	pushl	$0
	call	set_pos
	addl	$16, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	screen_clear, .-screen_clear
	.globl	kernel_main
	.type	kernel_main, @function
kernel_main:
.LFB4:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	$1819043176, -16(%ebp)
	movw	$111, -12(%ebp)
	call	screen_clear
	movw	$0, -10(%ebp)
	jmp	.L12
.L13:
	movzwl	-10(%ebp), %eax
	movzbl	-16(%ebp,%eax), %eax
	movsbl	%al, %edx
	movzwl	-10(%ebp), %eax
	subl	$4, %esp
	pushl	%edx
	pushl	$0
	pushl	%eax
	call	screen_putc
	addl	$16, %esp
	addw	$1, -10(%ebp)
.L12:
	cmpw	$4, -10(%ebp)
	jbe	.L13
	nop
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE4:
	.size	kernel_main, .-kernel_main
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB5:
	.cfi_startproc
	movl	(%esp), %eax
	ret
	.cfi_endproc
.LFE5:
	.section	.text.__x86.get_pc_thunk.dx,"axG",@progbits,__x86.get_pc_thunk.dx,comdat
	.globl	__x86.get_pc_thunk.dx
	.hidden	__x86.get_pc_thunk.dx
	.type	__x86.get_pc_thunk.dx, @function
__x86.get_pc_thunk.dx:
.LFB6:
	.cfi_startproc
	movl	(%esp), %edx
	ret
	.cfi_endproc
.LFE6:
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
