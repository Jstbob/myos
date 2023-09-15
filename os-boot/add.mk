CFLAG := -g -m32
cc := gcc

.c.o:
	$(cc) $(CFLAG) -c $<

.S.o:
	$(cc) $(CFLAG) -c $< 

add.out: add.o test_asm.o
	# echo $<
	# echo $*
	$(cc) $(CFLAG) $? -o $@
