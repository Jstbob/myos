qemu: kernel.img
	qemu-system-i386 -kernel kernel.img -m 256M

qemu-gdb: kernel.img
	qemu-system-i386 -kernel kernel.img -m 256M -s -S -serial stdio

%.s.o: %.s
	as --32 $< -o $@

%.c.o: %.c
	gcc -m32 -c $< -o $@ -nostdlib -I /usr/include/x86_64-linux-gnu

SRCS := $(shell find . -name "*.c" -or -name "*.s" -type f)
OBJS := $(shell find . -name "*.o" -type f)

kernel.img: $(OBJS)
	ld -m elf_i386 -T linker.ld -o $@ $?

clean:
	rm -rf *.o *.img