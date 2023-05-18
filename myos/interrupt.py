str='''\
#include \"descriptor_tables.h\"\n
.section .text\n\
.extern isr_common_stub\n'''

head='''.global isr{}\n'''

shell_code='''\
isr{}:
\tcli
\tpush ${}
\tjmp isr_common_stub
'''

with open("interrupt.s", "tw") as f:
    f.write(str)
    for i in range(0,32):
        f.write(head.format(i))
    for i in range(0,32):
        f.write(shell_code.format(i,i))


fun_txt="idt_set_gate({}, (uint32_t)isr{}, 0x08, 0x8E);\n"
isr_txt="extern void isr{}();\n"

with open("interrupt.txt","tw") as f:
    for i in range(0,32):
        f.write(fun_txt.format(i,i))
    f.write("\n")
    for i in range(0,32):
        f.write(isr_txt.format(i))