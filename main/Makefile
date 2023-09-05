CFLAGS := -m32 -nostdlib -g

# 不要使用.s，.s不能引用宏定义头
SRCS := $(shell find . -type f -name "*.c" -or -name "*.S")
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
	rm -rf *.o

qemu-debug: $(PROJECT_NAME).elf
	qemu-system-i386 -s -S -kernel $(PROJECT_NAME).elf
