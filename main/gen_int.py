with open("gen_int.txt", "w") as f:
#     for i in range(256):
#             f.write('''
# int{}:
#     cli
#     pusha
#     push ${}
#     jmp int_com_handler
#         '''.format(i,i))

    # f.write("\n")        

    for i in range(256):
        f.write("set_gate({}, PRI_INT_GATE, 0x08, (uint32_t)&int{});\n".format(i,i))

    # f.write("\n")        

    # for i in range(256):
    #     f.write(".global int{}\n".format(i))

    # f.write("\n")        

    # for i in range(256):
    #     f.write("extern void int{}();\n".format(i))
    
    # f.write("\n")  