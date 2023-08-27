CFLAGS := -m32 -Os -fno-pic -fno-pie -fno-strict-aliasing -finline-functions -ffreestanding -mgeneral-regs-only -g

SRCS := $(shell find . -type f -name "*.c" -or -name "*.s")
OBJS := $(SRCS:%=%.o)

%.s.o: %.s
	as --32 -g $< -o $@

%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel: $(OBJS)
	ld -m elf_i386 -T linker.ld $? -o $@.elf

qemu:
	qemu-system-i386 -m 128M -s -S -kernel kernel.elf -machine type=pc-i440fx-3.1

qemu-cd:
	qemu-system-i386 -m 128M -s -S -boot d -cdrom kernel.iso

qemu-iso:
	qemu-system-i386 -m 128M -boot d -cdrom kernel.iso

.PHYON:
clean:
	rm -rf *.o

.PHYON:
boot-iso:
	cp ./kernel.elf ./iso/boot/ -f
	grub-mkrescue -o kernel.iso iso/
