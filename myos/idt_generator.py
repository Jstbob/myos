idt = "set_idt_entry( {}, (uint32_t)isr{} , 0x08, 0x8E);"

isr = "extern void isr{}();"

global_isr = ".global isr{}"

asm='''\
isr{}:
    cli
    push ${}
    jmp handler 
'''

with open("idt_generator.txt","wt") as f:
    for i in range(0,32):
        f.write(idt.format(i,i))
        f.write("\n")

    for i in range(0,32):
        f.write(isr.format(i));
        f.write("\n")

    for i in range(0,32):
        f.write(global_isr.format(i))
        f.write("\n")

    for i in range(0,32):
        f.write(asm.format(i,i))
        f.write("\n")

    for i in range(0,32):
        f.write('asm volatile("int ${}");'.format(i))
        f.write("\n")