#include "monitor.h"
#include "multiboot.h"
#include "test.h"
#include <stdint.h>

uint32_t physical_memory_size = 0;

static void cal_physical_memory_size(struct multiboot_info *mbi) {
    if (mbi->flags & MULTIBOOT_INFO_MEM_MAP) {
        /* Iterate over memory map to calculate memory size */
        multiboot_memory_map_t *mmap;
        for (mmap = (multiboot_memory_map_t *)mbi->mmap_addr;
             (uint32_t)mmap < mbi->mmap_addr + mbi->mmap_length;
             mmap = (multiboot_memory_map_t *)((uint32_t)mmap + mmap->size
                                               + sizeof(mmap->size))) {
            if (mmap->type == MULTIBOOT_MEMORY_AVAILABLE) {
                physical_memory_size += mmap->len;
            }
        }
    } else {
        /* Use upper and lower memory size fields */
        physical_memory_size = mbi->mem_lower + mbi->mem_upper;
    }
}

int kernel_main(struct multiboot_info *mbi, uint32_t initial_stack) {
    cal_physical_memory_size(mbi);
#ifdef DEBUG
    test_main();
#else
    /*  TODO:
     *  init_monitor();
     *  init_descriptor_tables();   // gdt, idt, irq
     *  init_timer(50);
     *  init_paging();
     *  init_tasking();
     *  init_root_path();
     *  init_syscall();
     *  init_first_process();
     *  run_process_loop();
     */
#endif
}
