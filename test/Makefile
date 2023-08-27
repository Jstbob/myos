elf:
	as --32 -g boot.S -o boot.o
	gcc -m32 -Os -fno-pic -fno-pie -fno-strict-aliasing -finline-functions -ffreestanding -mgeneral-regs-only -g -c kernel.c
	ld -m elf_i386 boot.o kernel.o -T link.ld -o kernel.elf

qemu:
	qemu-system-i386 -kernel a.out -machine type=pc-i440fx-3.1 -s -S

check:
	grub-file --is-x86-multiboot2 a.out

elf:
	as --32 -g boot_elf.s -o boot_elf.o
	ld -m elf_i386 boot_elf.o -T link_elf.ld

clean:
	rm -rf *.o *.out* *.img*

qemu-cd:
	qemu-system-i386 -m 128M -boot d -cdrom kernel.iso -s -S

qemu-boot:
	qemu-system-i386 -m 128M -cdrom kernel.iso

.PHYON:
boot-iso:
	cp ./kernel.elf ./iso/boot/ -f
	grub-mkrescue -o kernel.iso iso/
