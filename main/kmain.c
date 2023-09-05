#include "boot.h"
#include "multiboot.h"
#include <stdint.h>


// pd只保存pt的22位，必须要4K对齐
[[gnu::aligned(4096)]] uint32_t kernel_pt[KERNEL_PAGE_ENTRIES];

// 设置内核32MB分页，pd中为pt[n]的指针 | 0x7
// 设定内核占用目录为8个目录，0-7
uint32_t kernel_pd[PD_COUNT];

int test_page = 0x20;

// 进入kmain时，假设所有物理内存页都是有效的
void kmain(struct multiboot_info *info) {
    test_page = 0x30;
}

