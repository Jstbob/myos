.section .data
addr:
    .byte 1, 2, 3, 4
direct_addr:
    .fill 4

.section .text
.global main
main:
    mov %esp, %ebx  # register -> register
    mov $0x40000, %ecx      # except: ecx = 0x40000
    mov $addr, %edx         # except: edx = addr
    mov %edx, direct_addr   # register -> memory
    mov direct_addr, %eax   # except: eax = addr
    ret

