print_helloworld: print_helloworld.s
	gcc -c $@.s -no-pie
	gcc $@.o -o $@.out -no-pie

index_addr: index_addr.s
	gcc -c $@.s -m32
	# gcc $@.s -o $@.out -m32
	ld -m elf_i386 -o $@.out $@.o -e main