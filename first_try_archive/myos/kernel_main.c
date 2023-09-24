#include "descriptor_tables.h"
#include "monitor.h"
#include "multiboot.h"
#include "test.h"
#include "vfs.h"
#include <stdint.h>

const uint32_t physical_memory_size = 128 * 1024 * 1024;

static void cal_physical_memory_size(struct multiboot_info *mbi) {
    // if (mbi->flags & MULTIBOOT_INFO_MEM_MAP) {
    //     /* Iterate over memory map to calculate memory size */
    //     multiboot_memory_map_t *mmap;
    //     for (mmap = (multiboot_memory_map_t *)mbi->mmap_addr;
    //          (uint32_t)mmap < mbi->mmap_addr + mbi->mmap_length;
    //          mmap = (multiboot_memory_map_t *)((uint32_t)mmap + mmap->size
    //                                            + sizeof(mmap->size))) {
    //         if (mmap->type == MULTIBOOT_MEMORY_AVAILABLE) {
    //             physical_memory_size += mmap->len;
    //         }
    //     }
    // } else {
    //     /* Use upper and lower memory size fields */
    //     physical_memory_size = mbi->mem_lower + mbi->mem_upper;
    // }
    // physical_memory_size = physical_memory_size - physical_memory_size %
    // 4096;
    // physical_memory_size = 128 * 1024 * 1024;   // 固定128MB
}

#define DEBUG

extern uint32_t kernel_end_offset;

int kernel_main(struct multiboot_info *mbi, uint32_t initial_stack) {
    // cal_physical_memory_size(mbi);
    // test_main();

    init_monitor();
    monitor_write_msg("helloworld\n");
    init_descriptor_tables();
    // asm volatile("int $0x8");
    // asm volatile("int $0x6");
    uint32_t kernel_size = (uint32_t)&kernel_end_offset;
    // init_descriptor_tables();
    uint32_t ptr = (uint32_t)mbi;
    monitor_write_hex((char *)ptr, sizeof(uint32_t));
    monitor_write_char('\n');
    monitor_write_hex((char *)&kernel_size, sizeof(uint32_t));
    monitor_write_char('\n');
    // uint32_t initrd_location = *((uint32_t *)mbi->mods_addr);
    // uint32_t initrd_end = *(uint32_t *)(mbi->mods_addr + 4);
    init_root_node(0x10A000);
    print_first_filename();
}
