#ifndef _MEM_H_
#define _MEM_H_

#include "boot.h"
#include <stdint.h>

// 内核堆内存大小 _end - 32MB，
// 16MB以下为小内存分配，16MB以上为大内存分配
// 多于4096的都为大内存分配
extern uint32_t _bin_end;

struct obj_header;

struct [[gnu::packed]] obj {
    uint32_t size;
    struct obj_header *back_ptr;
    unsigned char data[];
};

struct [[gnu::packed]] obj_header {
    uint32_t size;
    struct obj *p_hole;
};

#define OBJ_COUNT 1024

struct [[gnu::packed]] kmem_t {
    struct obj_header header[OBJ_COUNT];
    unsigned char raw[];
};

static struct kmem_t *kmem;

void init_kernel_heap();
void *kmalloc(uint32_t size);
void kfree(void *ptr);

#endif
