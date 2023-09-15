#include "boot.h"
#include "console.h"
#include "idt.h"
#include "mem_r.h"
#include "multiboot.h"
#include "pic.h"
#include <stdint.h>

// pd只保存pt的22位，必须要4K对齐
[[gnu::aligned(4096)]] uint32_t kernel_pt[KERNEL_PAGE_ENTRIES];

// 设置内核32MB分页，pd中为pt[n]的指针 | 0x7
// 每个页目录占4MB，共需8个页目录，1目录+1表=2*4096字节
uint32_t kernel_pd[PD_COUNT];

// 进入kmain时，假设所有物理内存页都是有效的
void kmain(struct multiboot_info *info) {
    console_init();
    init_idt();
    init_mem_heap();
    init_pic();
}
