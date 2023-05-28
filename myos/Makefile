ifeq ($(DEBUG),1)
%.s.o: %.s
	as --32 $< -o $@ -g

%.c.o: %.c
	gcc -m32 -c $< -o $@ -nostdlib -I /usr/include/x86_64-linux-gnu -g -DDEBUG

SRCS := $(shell find . -name "*.c" -or -name "*.s" ! -name "test*" -type f)
else
%.s.o: %.s
	as --32 $< -o $@

%.c.o: %.c
	gcc -m32 -c $< -o $@ -nostdlib -I /usr/include/x86_64-linux-gnu

SRCS := $(shell find . -name "*.c" -or -name "*.s" -type f)
endif

OBJS := $(SRCS:%=%.o)

kernel.img: $(OBJS)
	ld -m elf_i386 -T linker.ld -o $@ $?

qemu: kernel.img
	qemu-system-i386 -kernel kernel.img -m 128M		# 使用128M内存

qemu-gdb: kernel.img
	qemu-system-i386 -kernel kernel.img -m 128M -s -S -serial stdio

clean:
	rm -rf *.o *.img