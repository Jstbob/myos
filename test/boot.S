.set MAGIC, 0xe85250d6
.set ARCHITECTURE, 0
.set HEAD_LENGTH, head_end - head
.set CHECKSUM, - (MAGIC + HEAD_LENGTH)

.section .boot

.align  8
head:
.long MAGIC
.long ARCHITECTURE
.long HEAD_LENGTH
.long CHECKSUM

// .extern phys
// .extern bss_start
// .extern _end

// /* Address tag */
// .align 8
// mb2_tag_addr:
// .word 2
// .word 1
// .long 24
// .long head
// .long phys
// .long bss_start
// .long _end

// /* Entry tag */
// .align 8
// mb2_tag_entry:
// .word 3
// .word 1
// .long 12
// .long _start

// /* Framebuffer tag */
// .align 8
// mb2_tag_fb:
// .word 5
// .word 1
// .long 20
// .long 800
// .long 600
// .long 32

// .align 8
// .word 4
// .word 1
// .long 12
// .long 2 /* We support EGA text, but don't require it */

// /* Modules must be aligned */
// .align 8
// .word 6
// .word 0
// .long 8

/* End tag */
.align 8
.word 0
.word 0
.long 8
head_end:


.section .text
.extern cmain
.global _start
_start:
        movl $stack_top, %esp
        // pushl $0
        // popf
        pushl %ebx
        pushl %eax
        call cmain

loop:
        hlt
        jmp loop

.section .stack
stack_bottom:
.skip 16384
stack_top: