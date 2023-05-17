	.file	"monitor.c"
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
	movl	8(%ebp), %eax
	movb	%al, -4(%ebp)
	movsbw	-4(%ebp), %ax
	orb	$15, %ah
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	to_char16, .-to_char16
	.globl	monitor_set_cursor
	.type	monitor_set_cursor, @function
monitor_set_cursor:
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
	movl	8(%ebp), %eax
	movzwl	4(%eax), %ecx
	movl	%ecx, %eax
	sall	$2, %eax
	addl	%ecx, %eax
	sall	$4, %eax
	movl	%eax, %ecx
	movl	8(%ebp), %eax
	movzwl	6(%eax), %eax
	addl	%ecx, %eax
	movw	%ax, -10(%ebp)
	movzwl	-10(%ebp), %eax
	subl	$12, %esp
	pushl	%eax
	movl	%edx, %ebx
	call	_asm_set_pos@PLT
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
	.size	monitor_set_cursor, .-monitor_set_cursor
	.globl	monitor_scroll
	.type	monitor_scroll, @function
monitor_scroll:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%esi
	pushl	%ebx
	subl	$16, %esp
	.cfi_offset 6, -12
	.cfi_offset 3, -16
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movw	$1, -10(%ebp)
	jmp	.L5
.L8:
	movw	$0, -12(%ebp)
	jmp	.L6
.L7:
	movl	8(%ebp), %eax
	movl	(%eax), %ecx
	movzwl	-10(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$5, %eax
	subl	$160, %eax
	leal	(%ecx,%eax), %esi
	movzwl	-12(%ebp), %ecx
	movl	8(%ebp), %eax
	movl	(%eax), %ebx
	movzwl	-10(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$5, %eax
	addl	%eax, %ebx
	movzwl	-12(%ebp), %eax
	movzwl	(%esi,%ecx,2), %edx
	movw	%dx, (%ebx,%eax,2)
	addw	$1, -12(%ebp)
.L6:
	cmpw	$78, -12(%ebp)
	jbe	.L7
	addw	$1, -10(%ebp)
.L5:
	cmpw	$23, -10(%ebp)
	jbe	.L8
	movw	$0, -14(%ebp)
	jmp	.L9
.L10:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	3840(%eax), %esi
	movzwl	-14(%ebp), %ebx
	pushl	$0
	call	to_char16
	addl	$4, %esp
	movw	%ax, (%esi,%ebx,2)
	addw	$1, -14(%ebp)
.L9:
	cmpw	$78, -14(%ebp)
	jbe	.L10
	nop
	nop
	leal	-8(%ebp), %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	monitor_scroll, .-monitor_scroll
	.globl	monitor_putc
	.type	monitor_putc, @function
monitor_putc:
.LFB3:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	12(%ebp), %ecx
	movl	16(%ebp), %edx
	movl	20(%ebp), %eax
	movw	%cx, -28(%ebp)
	movw	%dx, -32(%ebp)
	movb	%al, -36(%ebp)
	movsbl	-36(%ebp), %eax
	pushl	%eax
	call	to_char16
	addl	$4, %esp
	movw	%ax, -10(%ebp)
	movl	8(%ebp), %eax
	movl	(%eax), %ecx
	movzwl	-28(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$5, %eax
	addl	%eax, %ecx
	movzwl	-32(%ebp), %eax
	movzwl	-10(%ebp), %edx
	movw	%dx, (%ecx,%eax,2)
	movl	8(%ebp), %eax
	movzwl	4(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movw	%dx, 4(%eax)
	movl	8(%ebp), %eax
	movzwl	4(%eax), %eax
	cmpw	$79, %ax
	jbe	.L12
	movl	8(%ebp), %eax
	movzwl	6(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movw	%dx, 6(%eax)
	movl	8(%ebp), %eax
	movzwl	4(%eax), %ecx
	movzwl	%cx, %eax
	imull	$52429, %eax, %eax
	shrl	$16, %eax
	movl	%eax, %edx
	shrw	$6, %dx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$4, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	movl	8(%ebp), %eax
	movw	%dx, 4(%eax)
.L12:
	movl	8(%ebp), %eax
	movzwl	6(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movw	%dx, 6(%eax)
	movl	8(%ebp), %eax
	movzwl	6(%eax), %eax
	cmpw	$23, %ax
	jbe	.L13
	pushl	8(%ebp)
	call	monitor_scroll
	addl	$4, %esp
.L13:
	subl	$12, %esp
	pushl	8(%ebp)
	call	monitor_set_cursor
	addl	$16, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	monitor_putc, .-monitor_putc
	.globl	monitor_cursor_zero
	.type	monitor_cursor_zero, @function
monitor_cursor_zero:
.LFB4:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	8(%ebp), %eax
	movw	$0, 6(%eax)
	movl	8(%ebp), %eax
	movzwl	6(%eax), %edx
	movl	8(%ebp), %eax
	movw	%dx, 4(%eax)
	subl	$12, %esp
	pushl	8(%ebp)
	call	monitor_set_cursor
	addl	$16, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE4:
	.size	monitor_cursor_zero, .-monitor_cursor_zero
	.globl	monitor_init
	.type	monitor_init, @function
monitor_init:
.LFB5:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	subl	$12, %esp
	pushl	8(%ebp)
	call	monitor_cursor_zero
	addl	$16, %esp
	movl	8(%ebp), %eax
	movl	$753664, (%eax)
	movw	$0, -10(%ebp)
	jmp	.L16
.L19:
	movw	$0, -12(%ebp)
	jmp	.L17
.L18:
	movzwl	-12(%ebp), %edx
	movzwl	-10(%ebp), %eax
	pushl	$0
	pushl	%edx
	pushl	%eax
	pushl	8(%ebp)
	call	monitor_putc
	addl	$16, %esp
	addw	$1, -12(%ebp)
.L17:
	cmpw	$79, -12(%ebp)
	jbe	.L18
	addw	$1, -10(%ebp)
.L16:
	cmpw	$24, -10(%ebp)
	jbe	.L19
	subl	$12, %esp
	pushl	8(%ebp)
	call	monitor_cursor_zero
	addl	$16, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE5:
	.size	monitor_init, .-monitor_init
	.globl	_kernel_main
	.type	_kernel_main, @function
_kernel_main:
.LFB6:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	subl	$12, %esp
	leal	-20(%ebp), %eax
	pushl	%eax
	call	monitor_init
	addl	$16, %esp
	movl	$1819043176, -26(%ebp)
	movw	$111, -22(%ebp)
	movl	$0, -12(%ebp)
	jmp	.L21
.L22:
	leal	-26(%ebp), %edx
	movl	-12(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movsbl	%al, %edx
	movl	-12(%ebp), %eax
	movzwl	%ax, %eax
	pushl	%edx
	pushl	%eax
	pushl	$0
	leal	-20(%ebp), %eax
	pushl	%eax
	call	monitor_putc
	addl	$16, %esp
	addl	$1, -12(%ebp)
.L21:
	movl	-12(%ebp), %eax
	cmpl	$4, %eax
	jbe	.L22
	nop
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE6:
	.size	_kernel_main, .-_kernel_main
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB7:
	.cfi_startproc
	movl	(%esp), %eax
	ret
	.cfi_endproc
.LFE7:
	.section	.text.__x86.get_pc_thunk.dx,"axG",@progbits,__x86.get_pc_thunk.dx,comdat
	.globl	__x86.get_pc_thunk.dx
	.hidden	__x86.get_pc_thunk.dx
	.type	__x86.get_pc_thunk.dx, @function
__x86.get_pc_thunk.dx:
.LFB8:
	.cfi_startproc
	movl	(%esp), %edx
	ret
	.cfi_endproc
.LFE8:
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
