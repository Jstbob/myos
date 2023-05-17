
qemu: kernel.img
	qemu-system-i386 -kernel kernel.img -m 256M

qemu-gdb: kernel.img
	qemu-system-i386 -kernel kernel.img -m 256M -s -S -serial stdio

kernel.img: boot.o screen.o monitor.o
	ld -m elf_i386 -T linker.ld -o $@ $?

boot.o: boot.s
	as --32 $? -o $@

screen.o: screen.s
	as --32 $? -o $@

monitor.o: monitor.c
	gcc -m32 -S $? -I /usr/include/x86_64-linux-gnu
	as --32 $*.s -o $@

clean:
	rm -f *.o *.img