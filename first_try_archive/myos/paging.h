#ifndef _PAGING_H
# define _PAGING_H

# include "common.h"
# include "descriptor_tables.h"
# include <stddef.h>
# include <stdint.h>

/*
 * 分页属性描述符
 * |31 - - - - - 12|11 - 9|8 - 7|6|5|4 - 3| 2 | 1 |0|
 * |physical offset| AVAIL| RSVD|D|A|RSVD |U/S|R/W|P|
 *                                          s   1  s
 * 开启分页的步骤：
 *      1. 设置好二级分页目录；
 *      2. 设置 CR3 为 PD 指针；
 *      3. 设置 CR0 的 PG 位；| 0x80000000
 * Page faults, cpu 会设置 CR2 寄存器；
 * P: 页面是否存在，1：存在，0：不存在
 * R/W：页面是否可写，1：可写，0：不可写
 * U/S：内存访问在什么模式下，1：用户模式，0：内核模式；
 * Reserverd: CPU 保留，不使用
 * A：如果内页有权限访问，由 CPU 设置
 * D：如果内存已经被写入，由 CPU 设置
 * AVAIL：这3位是被保留，供内核下使用
 * Page frame address: 映射物理块的高20位，低12位固定表示4KB，不用表示
 * Ref from: http://www.jamesmolloy.co.uk/tutorial_html/6.-Paging.html
 */
struct page_table_t {
    uint32_t entries[1024];
};

struct page_directory_t {
    struct page_table_t *page_directories[1024];
    uint32_t tables_physical[1024];
};

// struct obj_t {
//     struct obj_t *pre;
//     struct obj_t *next;
//     uint32_t size : 31; // 内存块的大小
//     uint32_t used : 1; // 内存块是否被使用
//     unsigned char context[];
// } __attribute__((packed));

// // 堆链表
// struct heap_t {
//     struct obj_t *head;
// };

struct block_t {
    struct block_t *next;
    uint32_t block_size;
    unsigned char used;
    unsigned char block[];
} __attribute__((packed));

static const uint32_t block_header_size = sizeof(struct block_t);

void init_paging();
void *kalloc(uint32_t size);
void kfree(void *ptr);

#endif

// // // 上述代码有BUG，调试不出来

// #ifndef _PAGING_H
// #define _PAGING_H

// #include <stdint.h>

// typedef struct page {
//     uint32_t present : 1;  // Page present in memory
//     uint32_t rw : 1;       // Read-only if clear, readwrite if set
//     uint32_t user : 1;     // Supervisor level only if clear
//     uint32_t accessed : 1; // Has the page been accessed since last refresh?
//     uint32_t dirty : 1;    // Has the page been written to since last
//     uint32_t unused : 7;   // Amalgamation of unused and reserved
//     uint32_t frame : 20;   // Frame address (shifted right 12 bits)
// } page_t;

// typedef struct page_table {
//     page_t pages[1024];
// } page_table_t;

// typedef struct page_directory {
//     /**
//        Array of pointers to pagetables.
//     **/
//     page_table_t *tables[1024];
//     /**
//        Array of pointers to the pagetables above, but gives their *physical*
//        location, for loading into the CR3 register.
//     **/
//     uint32_t tablesPhysical[1024];

//     /**
//        The physical address of tablesPhysical. This comes into play
//        when we get our kernel heap allocated and the directory
//        may be in a different location in virtual memory.
//     **/
//     uint32_t physicalAddr;
// } page_directory_t;

// /**
//    Sets up the environment, page directories etc and
//    enables paging.
// **/
// void initialise_paging();

// /**
//    Causes the specified page directory to be loaded into the
//    CR3 register.
// **/
// void switch_page_directory(page_directory_t *new);

// /**
//    Retrieves a pointer to the page required.
//    If make == 1, if the page-table in which this page should
//    reside isn't created, create it!
// **/
// page_t *get_page(uint32_t address, int make, page_directory_t *dir);

// #endif