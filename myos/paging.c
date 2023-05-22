#include "paging.h"
#include <stdint.h>

union page_t {
    struct {
        uint32_t present : 1;
        uint32_t rw : 1;
        uint32_t user : 1;
        uint32_t accessed : 1;
        uint32_t dirty : 1;
        uint32_t unused : 7;
        uint32_t frame : 20;
    };
    uint32_t total;
};

struct page_table_t {
    union page_t entries[1024];
};

struct page_directory_t {
    struct page_table_t *tables[1024];
};

uint32_t present_index = 0;
struct page_directory_t page_directory;

extern uint32_t end;
uint32_t place_addr;

uint32_t kmalloc(uint32_t size) {
    uint32_t alloc_addr = place_addr;
    place_addr += size;
    return alloc_addr;
}

uint32_t const MEMORY_CAP = 128 * 1024 * 1024;  // 128MB
uint32_t const PAGE_PER = 4 * 1024;

void init_paging() {
    place_addr = end;
    uint32_t index = 0;
    for (uint32_t i = 0; i < 1024; ++i) {
        struct page_table_t *page_table
            = (struct page_table_t *)kmalloc(sizeof(*page_table));
        for (uint32_t j = 0; j < 1024; ++j) {
            union page_t page;
            if (index > MEMORY_CAP / PAGE_PER) {
                page.total = ((index * PAGE_PER) << 12) | 0x7;
            } else {
                page.total = ((index * PAGE_PER) << 12) | 0x6;
            }
            page_table->entries[j] = page;
            ++index;
        }
        page_directory.tables[i] = page_table;
    }

    asm volatile("mov %0, %%cr3" ::"r"(&page_directory));
    uint32_t cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000; // Enable paging!
    asm volatile("mov %0, %%cr0" ::"r"(cr0));
}
