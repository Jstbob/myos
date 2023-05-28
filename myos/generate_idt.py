file_name="generate_idt.txt"

def gen_asm():
    with open(file_name, "wt") as f:
        for i in range(0,32):
            f.write("extern void isr{}();\n".format(i))

        for i in range(0,32):
            f.write("register_idt( {}, (uint32_t)isr{} , 0x08, 0x8E, &idt_call_back_fun);\n".format(i,i))

        for i in range(0,32):
            if i==8 or i==10 or i==11 or i==12 or i==13 or i==14:
                f.write('''\
                    isr{}:
                        cli
                        push ${}
                        jmp isr_common_stub
                    \n'''.format(i,i))
            else:
                f.write('''\
                    isr{}:
                        cli
                        push $0
                        push ${}
                        jmp isr_common_stub
                    \n'''.format(i,i))
        
        for i in range(0,32):
            f.write(".global isr{}\n".format(i))

        for i in range(0,32):
            f.write('''\
    isr{}:
        cli
        push ${}
        jmp isr_common_stub
                \n'''.format(i,i))
            
        for i in range(32,48):
            f.write("register_idt({}, (uint32_t)&irq{}, 0x08, 0x8E, &idt_call_back_fun);\n".format(i,i-32))

        for i in range(32,48):
            f.write("extern void irq{}();\n".format(i-32))

        for i in range(32,48):
            f.write('''\
    irq{}:
        cli
        push ${}
        jmp isr_common_stub
                \n'''.format(i-32,i))
            
        for i in range(32,48):
            f.write(".global irq{}\n".format(i-32))



if __name__ == "__main__":
    import streamlit as st
    st.write('''\
# Helloworld
这是中文      ''')

