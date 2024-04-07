/* 
    Offset   Type     Field Name      Note
    0         u32     magic           required
    4         u32     architecture    required
    8         u32     header length   required
    12        u32     checksum        required
    16-XX             tags            required
*/

.section .multiboot2
.align 8

# multiboot2 magic header
.set MAGIC, 0xE85250D6
.set ARCHITECTURE, 0
.set HEADER_LENGTH, header_end - header_start
.set CHECKSUM, - (MAGIC + ARCHITECTURE + HEADER_LENGTH)

header_start:
.long MAGIC
.long ARCHITECTURE
.long HEADER_LENGTH
.long CHECKSUM

# end tag 
.word 0    
.word 0
.long 8
header_end:


.section .stack
.align 16
stack_bottom:
.fill 16384, 1, 0
stack_top:


.section .text
.global _entry
.extern kernel_main
_entry:
    cli
    movl $stack_top, %esp
    pushl %ebx
    call kernel_main
loop:
    hlt
    jmp loop
