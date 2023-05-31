#include "paging.h"
#include "common.h"
#include "descriptor_tables.h"
#include "monitor.h"
#include <stdint.h>

/* 思路：
 *  1. 获取物理内存的可用大小；
 *      bios 中断获取内存大小 - 内核尾指针
 *  2. 内核尾指针位置，就是物理内存分页的起始位置；（p, size）；
 *  3. 从起始位置进行4KB分页；
 *  4. 记录到内存二级目录中；
 *
 *  0 - kernel_end -> readonly page
 *  kernel_end - memory_max -> write and read page
 *
 *  内存布局：
 *  |   BIOS区      |
 *  |   内核代码区  |
 *  |   内核堆区    |
 *  |   用户代码区  |   获取总内存大小/2, 至内存总大小 - 16MB - 4kb *
 * 256，最多256个进程； 4kb＊256； |   用户栈区    |
 * 每个进程的栈区固定为4kb，4kb * 256; | 内存虚拟硬盘 |  16MB
 */

extern uint32_t kernel_end_offset;
extern uint32_t physical_memory_size;
extern idt_call_back idt_tables[256];

// static struct obj_t *kernel_heap;
static struct block_t *kernel_heap;
static struct page_directory_t *page_directory;
static struct page_directory_t *current_directory;
static struct page_table_t *page_table;

static void init_memory_heap(uint32_t base_addr, uint32_t size);
static void switch_page_directory(struct page_directory_t *dir);
static void page_faults_handler(struct registers_t *regs);

/*
 * 使用动态内存初始化分页目录
 * // 0 - 0x80000000 map-> 0 - physical_memory_size/2
 * // 0x80000000 map-> physical_memory_size / 2 - physical_memory_size
 */
void init_paging() {
    uint32_t kernel_boundary = physical_memory_size / 2;
    uint32_t space_mem = (uint32_t)&kernel_end_offset + 4096;
    uint32_t mem_start = space_mem - space_mem % 4096;
    space_mem
        = mem_start
          + 1024 * sizeof(struct page_table_t); // 固定值 0x110000 测试通过
    uint32_t size = kernel_boundary - space_mem;
    init_memory_heap(
        space_mem,
        size); // 初始化内核堆，内核堆是从kernel_end_offset之后开始，到总内存的1/2
#ifdef DEBUG
    void *test_kalloc = kalloc(4);
    uint32_t *ptr = (uint32_t *)kernel_boundary;
    *ptr = 0x6666;
#endif

    page_table = (struct page_table_t *)mem_start;
    page_directory
        = (struct page_directory_t *)(mem_start
                                      - sizeof(struct page_directory_t));
    for (int i = 0; i < 1024; ++i) {
        page_directory->page_directories[i] = &page_table[i];
        page_directory->tables_physical[i] = (uint32_t)&page_table[i] | 0x07;
    }

    for (int i = 0; i < 1024; ++i) {
        for (int j = 0; j < 1024; ++j) {
            uint32_t addr = (i << 22) | (j << 12);
            if (addr < physical_memory_size) {
                page_table[i].entries[j] = addr | 0x07;
            } else {
                page_table[i].entries[j] = addr | 0x06;
            }
        }
    }

    // bug: can't write cr3
    // for (int i = 0; i < 1024; ++i) {
    //     page_directory.page_directories[i]
    //         = (struct page_table_t *)kalloc(sizeof(struct page_table_t));
    //     page_directory.tables_physical[i]
    //         = (uint32_t)page_directory.page_directories[i] | 0x03;
    //     for (int j = 0; j < 1024; ++j) {
    //         uint32_t addr = (i << 22) | (j << 12);
    //         // page_directory.page_directories[i]->entries[j] = addr | 0x03;
    //         if (addr < 0x80000000) {
    //             if (addr < kernel_boundary) {
    //                 page_directory.page_directories[i]->entries[j]
    //                     = addr | 0x03; // 内核区、页面存在，0b011
    //             } else {
    //                 page_directory.page_directories[i]->entries[j]
    //                     = addr | 0x02; // 内核区、页面不存在，0b010
    //             }
    //         } else {
    //             if (addr < (physical_memory_size + 0x80000000)) {
    //                 page_directory.page_directories[i]->entries[j]
    //                     = (addr - 0x80000000 + kernel_boundary)
    //                       | 0x07; // 用户区、页面存在，0b111
    //             } else {
    //                 page_directory.page_directories[i]->entries[j]
    //                     = addr | 0x06; // 用户区、页面不存在，0b110
    //             }
    //         }
    //     }
    // }
    idt_tables[14] = &page_faults_handler;

    switch_page_directory(page_directory);
}

static void page_faults_handler(struct registers_t *regs) {
    panic("page_faults_handler", __FILE__, __LINE__);
}

void *kalloc(uint32_t size) {
    // for (struct obj_t *obj_ptr = kernel_heap;
    //      !(obj_ptr->used) && obj_ptr->size > size; obj_ptr =
    // obj_ptr->next)
    //      {
    //     struct obj_t *right_part
    //         = (struct obj_t *)(obj_ptr + sizeof(struct obj_t)
    //                            + size); // 分裂未使用的内存块
    //     right_part->pre = obj_ptr;
    //     right_part->next = obj_ptr->next;
    //     right_part->size = obj_ptr->size - size - sizeof(struct obj_t);
    //     right_part->used = 0;
    //     obj_ptr->next->pre = right_part;
    //     obj_ptr->next = right_part;
    //     obj_ptr->size = size;
    //     obj_ptr->used = 1;
    //     return &(obj_ptr->context);
    // }
    // return NULL;
    struct block_t *node = kernel_heap;
    while (node) {
        if (node->used) {
            node = node->next;
            continue;
        } else {
            if (node->block_size >= size) {
                struct block_t *right_part = node + block_header_size + size;
                right_part->next = node->next;
                right_part->block_size
                    = node->block_size - block_header_size - size;
                right_part->used = 0;
                node->next = right_part;
                node->block_size = size;
                node->used = 1;
                return &node->block;
            } else {
                panic("Not enough memory to allocate", __FILE__, __LINE__);
            }
        }
    }
}

void kfree(void *ptr) {
    // struct obj_t *obj = (struct obj_t *)(ptr - sizeof(struct obj_t));
    // if (obj->pre && !(obj->pre->used) && obj->next && !(obj->next->used))
    // {
    //     struct obj_t *left_part = obj->pre;
    //     struct obj_t *right_part = obj->next;
    //     left_part->next = right_part;
    //     left_part->size = left_part->size + obj->size +
    //     right_part->size;
    // }
    // if (obj->pre && !(obj->pre->used)) {
    //     struct obj_t *left_part = obj->pre;
    //     left_part->next = obj->next;
    //     left_part->size += obj->size;
    // }
    // if (obj->next && !(obj->next->used)) {
    //     struct obj_t *right_part = obj->next;
    //     obj->next = right_part->next;
    //     obj->size += right_part->size;
    // }
    // ptr = NULL;
    struct block_t *node = (struct block_t *)(ptr + block_header_size);
    if (node->next->used) {
        node->used = 0;
    } else {
        node->block_size
            = node->block_size + block_header_size + node->next->block_size;
        node->used = 0;
        node->next = node->next->next;
    }
}

static void init_memory_heap(uint32_t base_addr, uint32_t size) {
    // kernel_heap = (struct obj_t *)base_addr;
    // kernel_heap->pre = NULL;
    // kernel_heap->next = NULL;
    // kernel_heap->size = size - sizeof(struct obj_t);
    // kernel_heap->used = 0;
    kernel_heap = (struct block_t *)base_addr;
    kernel_heap->next = 0;
    kernel_heap->block_size = size - block_header_size;
    kernel_heap->used = 0;
}

static void switch_page_directory(struct page_directory_t *dir) {
    // asm volatile("cli");
    current_directory = dir;
    asm volatile("mov %0, %%cr3" ::"r"(&dir->tables_physical));
    uint32_t cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000; // Enable paging!
    asm volatile("mov %0, %%cr0" ::"r"(cr0));
    // asm volatile("sti");
}

// // // 上述代码有BUG，调试不出来

// #include "paging.h"
// #include "common.h"
// #include "kheap.h"
// #include <stdint.h>

// // The kernel's page directory
// page_directory_t *kernel_directory = 0;

// // The current page directory;
// page_directory_t *current_directory = 0;

// uint32_t *frames;
// uint32_t nframes;

// // extern uint32_t physical_memory_size;
// static uint32_t placement_address = 128 * 1024 * 1024; // 128MB

// // Macros used in the bitset algorithms.
// #define INDEX_FROM_BIT(a) (a / (8 * 4))
// #define OFFSET_FROM_BIT(a) (a % (8 * 4))

// // Static function to set a bit in the frames bitset
// static void set_frame(uint32_t frame_addr) {
//     uint32_t frame = frame_addr / 0x1000;
//     uint32_t idx = INDEX_FROM_BIT(frame);
//     uint32_t off = OFFSET_FROM_BIT(frame);
//     frames[idx] |= (0x1 << off);
// }

// // Static function to clear a bit in the frames bitset
// static void clear_frame(uint32_t frame_addr) {
//     uint32_t frame = frame_addr / 0x1000;
//     uint32_t idx = INDEX_FROM_BIT(frame);
//     uint32_t off = OFFSET_FROM_BIT(frame);
//     frames[idx] &= ~(0x1 << off);
// }

// // Static function to test if a bit is set.
// static uint32_t test_frame(uint32_t frame_addr) {
//     uint32_t frame = frame_addr / 0x1000;
//     uint32_t idx = INDEX_FROM_BIT(frame);
//     uint32_t off = OFFSET_FROM_BIT(frame);
//     return (frames[idx] & (0x1 << off));
// }

// // Static function to find the first free frame.
// static uint32_t first_frame() {
//     uint32_t i, j;
//     for (i = 0; i < INDEX_FROM_BIT(nframes); i++) {
//         if (frames[i] != 0xFFFFFFFF) // nothing free, exit early.
//         {
//             // at least one bit is free here.
//             for (j = 0; j < 32; j++) {
//                 uint32_t toTest = 0x1 << j;
//                 if (!(frames[i] & toTest)) {
//                     return i * 4 * 8 + j;
//                 }
//             }
//         }
//     }
// }

// // Function to allocate a frame.
// void alloc_frame(page_t *page, int is_kernel, int is_writeable) {
//     if (page->frame != 0) {
//         return;
//     } else {
//         uint32_t idx = first_frame();
//         if (idx == (uint32_t)-1) {
//             // PANIC! no free frames!!
//         }
//         set_frame(idx * 0x1000);
//         page->present = 1;
//         page->rw = (is_writeable) ? 1 : 0;
//         page->user = (is_kernel) ? 0 : 1;
//         page->frame = idx;
//     }
// }

// // Function to deallocate a frame.
// void free_frame(page_t *page) {
//     uint32_t frame;
//     if (!(frame = page->frame)) {
//         return;
//     } else {
//         clear_frame(frame);
//         page->frame = 0x0;
//     }
// }

// void initialise_paging() {
//     // The size of physical memory. For the moment we
//     // assume it is 16MB big.
//     uint32_t mem_end_page = 0x1000000;

//     nframes = mem_end_page / 0x1000;
//     frames = (uint32_t *)kmalloc(INDEX_FROM_BIT(nframes));
//     memset(frames, 0, INDEX_FROM_BIT(nframes));

//     // Let's make a page directory.
//     kernel_directory = (page_directory_t
//     *)kmalloc_a(sizeof(page_directory_t)); current_directory =
//     kernel_directory;

//     // We need to identity map (phys addr = virt addr) from
//     // 0x0 to the end of used memory, so we can access this
//     // transparently, as if paging wasn't enabled.
//     // NOTE that we use a while loop here deliberately.
//     // inside the loop body we actually change placement_address
//     // by calling kmalloc(). A while loop causes this to be
//     // computed on-the-fly rather than once at the start.
//     int i = 0;
//     while (i < placement_address) {
//         // Kernel code is readable but not writeable from userspace.
//         alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
//         i += 0x1000;
//     }

//     // Now, enable paging!
//     switch_page_directory(kernel_directory);
// }

// void switch_page_directory(page_directory_t *dir) {
//     current_directory = dir;
//     asm volatile("mov %0, %%cr3" ::"r"(&dir->tablesPhysical));
//     uint32_t cr0;
//     asm volatile("mov %%cr0, %0" : "=r"(cr0));
//     cr0 |= 0x80000000; // Enable paging!
//     asm volatile("mov %0, %%cr0" ::"r"(cr0));
// }

// page_t *get_page(uint32_t address, int make, page_directory_t *dir) {
//     // Turn the address into an index.
//     address /= 0x1000;
//     // Find the page table containing this address.
//     uint32_t table_idx = address / 1024;
//     if (dir->tables[table_idx]) // If this table is already assigned
//     {
//         return &dir->tables[table_idx]->pages[address % 1024];
//     } else if (make) {
//         uint32_t tmp;
//         dir->tables[table_idx]
//             = (page_table_t *)kmalloc_ap(sizeof(page_table_t), &tmp);
//         dir->tablesPhysical[table_idx] = tmp | 0x7; // PRESENT, RW, US.
//         return &dir->tables[table_idx]->pages[address % 1024];
//     } else {
//         return 0;
//     }
// }
