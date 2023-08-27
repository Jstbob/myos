/* 
    Offset   Type     Field Name      Note
    0         u32     magic           required
    4         u32     architecture    required
    8         u32     header length   required
    12        u32     checksum        required
    16-XX             tags            required
*/

    .section .multiboot
.align 8
.extern load_address
.extern load_end_addr
.extern bss_end_addr

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

# addr tag
.word 2
.word 0
.long 24
.long header_start
.long load_address
.long load_end_addr
.long bss_end_addr

# entry tag
.word 3
.word 0
.long 12
.long entry

# flag console tag
.word 4
.word 0
.long 12
.long 0

# framebuffer tag
.word 5
.word 0
.long 20
.long 80
.long 25
.long 0

# module tag
.word 6
.word 0
.long 8

# end tag 
.word 0    
.word 0
.long 8
header_end:


    .section .bss
.align 16
stack_bottom:
.fill 16384, 1, 0
stack_top:

    .section .text
.global entry
.extern kernel_main

entry:
    movl $stack_top, %esp
    pushl %ebx
    call kernel_main
loop:
    hlt
    jmp loop
