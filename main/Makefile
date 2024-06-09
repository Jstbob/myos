CFLAGS := -nostdlib -fno-pic -fno-pie -fno-plt -no-pie -fno-stack-protector -g -m32 -o2

# Don't use ".s" file, can't inlcude define varible in ".s" file.
SRCS := $(shell find . -maxdepth 1 -type f -name "*.c" -not -name "*user.c" -or -name "*.S" -not -name "crt.S" \
	-not -name "int.S" -not -name "init.S")
OBJS := $(SRCS:%=%.o)
PROJECT_NAME := kernel

%.S.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PROJECT_NAME): $(OBJS)
	ld -m elf_i386 -T link.ld $? -o $@.elf

.PHYON:
clean:
	rm -rf *.o *.elf *.out

qemu-debug: $(PROJECT_NAME).elf
	qemu-system-i386 -s -S -kernel $(PROJECT_NAME).elf -m 128M

qemu: $(PROJECT_NAME).elf
	qemu-system-i386 -kernel $(PROJECT_NAME).elf -m 128M

# Create 4MB disk raw img.
fs.img:
	dd if=/dev/zero of=fs.img bs=1048576 count=4

create_fs.out: create_fs.cpp
	g++ $? -o $@ -g

fs_debug:
	gdbserver --multi 0.0.0.0:1234 create_fs.out

qemu-driver: $(PROJECT_NAME).elf
	qemu-system-i386 -s -S -kernel $(PROJECT_NAME).elf -drive file=fs.img,index=0,media=disk,format=raw -m 128M

qemu-driver-nodebug: $(PROJECT_NAME).elf
	qemu-system-i386 -kernel $(PROJECT_NAME).elf -drive file=fs.img,index=0,media=disk,format=raw -serial mon:stdio -m 128M
