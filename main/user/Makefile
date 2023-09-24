CFLAGS := -m32 -nostdlib -g -w

init.elf: init.c crt.S int.S
	gcc $(CFLAGS) -c crt.S -o crt.S.o
	gcc $(CFLAGS) -c init.S -o init.S.o
	gcc $(CFLAGS) -c init.c -o init.c.o
	ld -m elf_i386 -T link.ld crt.S.o init.S.o init.c.o -o init.elf
