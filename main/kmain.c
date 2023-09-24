#include "boot.h"
#include "console.h"
#include "fs.h"
#include "idt.h"
#include "mem_r.h"
#include "multiboot.h"
#include "pic.h"
#include "process.h"
#include <stdint.h>

[[gnu::aligned(4096)]] uint32_t kernel_pt[KERNEL_PAGE_ENTRIES];
uint32_t kernel_pd[PD_COUNT];
uint32_t kernel_call[256];

void init_call_func() {
    kernel_call[0] = &ls_dir; // ls
    kernel_call[1] = &cat;    // TODO, cat
}

// 进入kmain时，内存分页设置了4GB的空间
void kmain(struct multiboot_info *info) {
    console_init();
    init_call_func();
    init_available_mem(info->mem_upper);
    init_idt();
    init_mem_heap();
    init_fs();
    init_pic();
    test_cmd();
}
