#include "mem.h"
#include "boot.h"
#include "console.h"

void init_kernel_heap() {
    // 覆盖堆值
    unsigned char *start = (unsigned char *)_bin_end;
    uint32_t heap_size = KERNEL_MEMORY - _bin_end;
    while ((uint32_t)start < KERNEL_MEMORY) {
        *start = 0;
        ++start;
    }

    // 建立堆结构
    kmem = (struct kmem_t *)start;
    kmem->header[0].size
        = heap_size - sizeof(struct kmem_t) - sizeof(struct obj);
    kmem->header[0].p_hole = (struct obj *)kmem->raw;
    kmem->header[0].p_hole->size = kmem->header[0].size;
    kmem->header[0].p_hole->back_ptr = &kmem->header[0];
}

void swap(struct obj_header *a, struct obj_header *b) {
    struct obj_header tmp;
    tmp.p_hole = a->p_hole;
    tmp.size = a->size;
    a->p_hole = b->p_hole;
    a->size = b->size;
    b->p_hole = tmp.p_hole;
    b->size = tmp.size;
}

// 将kmem中的header将从小到大顺序排列，将size为0的放到最后
void sort_header() {
    for (uint32_t i = 0; i < OBJ_COUNT; ++i) {
        for (uint32_t j = i + 1; j < OBJ_COUNT; ++j) {
            struct obj_header *a = &kmem->header[i];
            struct obj_header *b = &kmem->header[j];
            if (b->size < a->size && b->size != 0) {
                swap(a, b);
            }
        }
    }
}

void *kmalloc(uint32_t size) {
    // 寻找第一个符合size大小的洞
    struct obj_header *min = 0;
    for (uint32_t i = 0; i <= OBJ_COUNT; ++i) {
        if (i == OBJ_COUNT) {
            panic("kmalloc fail, not found enough memory.");
        }

        if (kmem->header[i].size >= size + sizeof(struct obj)) {
            min = &kmem->header[i];
            break;
        }
    }

    struct obj *p = min->p_hole;
    p->back_ptr = 0; // 已使用的内存块，没有回链
    p->size = size;
    min->p_hole
        = (struct obj *)((unsigned char *)p + sizeof(struct obj) + p->size);
    min->size = min->size - size - sizeof(struct obj);
    min->p_hole->back_ptr = min; // 未使用的块有回链
    sort_header();
    return p->data;
}

void kfree(void *ptr) {
    struct obj *tmp = (struct obj *)((uint32_t)ptr - sizeof(struct obj));
    struct obj *right = (struct obj *)((unsigned char *)tmp + tmp->size
                                       + sizeof(struct obj));
    if (right->back_ptr) {
        tmp->back_ptr->p_hole = tmp;
        tmp->back_ptr->size = tmp->size + right->size + sizeof(struct obj);
    } else {
        for (uint32_t i = 0; i < OBJ_COUNT; ++i) {
            if (kmem->header[i].size == 0) {
                kmem->header[i].size = tmp->size;
                tmp->back_ptr = &kmem->header[i];
            }
        }
        sort_header();
    }
}
