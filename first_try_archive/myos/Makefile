ifeq ($(DEBUG),1)
%.s.o: %.s
	as --32 $< -o $@ -g

%.c.o: %.c
	gcc -m32 -c $< -o $@ -nostdlib -g -DDEBUG

SRCS := $(shell find . -name "*.c" -or -name "*.s" ! -name "test*" -type f)
else
%.s.o: %.s
	as --32 $< -o $@

%.c.o: %.c
	gcc -m32 -c $< -o $@ -nostdlib

SRCS := $(shell find . -name "*.c" -or -name "*.s" -type f)
endif

OBJS := $(SRCS:%=%.o)

kernel.img: $(OBJS)
	ld -m elf_i386 -T linker.ld -o $@ $?

# 使用128M内存
qemu: kernel.img
	qemu-system-i386 -kernel kernel.img -m 128M		

qemu-gdb: kernel.img
	qemu-system-i386 -kernel kernel.img -m 128M -s -S -serial stdio

clean:
	rm -rf *.o *.img* *.elf *.out

# 创建initrd.img自定义的文件系统
initrd.img: create_initrd.cpp
	g++ $? -o create_initrd.out
	./create_initrd.out

iso:
	cp -f kernel.img initrd.img ../iso/
	rm -f ../myos.iso
	grub-mkrescue -o ../myos.iso ../iso/

qemu-iso:
	qemu-system-i386 -cdrom ../myos.iso -m 128M

iso:
	qemu-system-i386 -cdrom ../myos.iso -m 128M -nographic
