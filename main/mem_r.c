#include "mem_r.h"
#include "boot.h"
#include "console.h"

void mem_cpy(void *src, void *des, uint32_t size) {
    for (uint32_t i = 0; i < size; ++i) {
        *((unsigned char *)des + i) = *((unsigned char *)src + i);
    }
}

void mem_set(void *src, uint32_t size, unsigned char c) {
    for (uint32_t i = 0; i < size; ++i) {
        *((unsigned char *)src + i) = c;
    }
}

void get_heap_start_size() {
    heap_size = KERNEL_MEMORY - (uint32_t)heap_start;
}

void init_mem_heap() {
    get_heap_start_size();
    mem_heap = (struct node *)heap_start;
    mem_set(mem_heap, 4096, 0); // 在qemu debug中必须清零
    mem_heap->previous = 0;
    mem_heap->next = 0;
    mem_heap->state = 0;
    mem_heap->size = heap_size - node_size;
}

void *krmalloc(uint32_t size) {
    struct node *tmp;
    // 寻找空闲且大小大于size的块
    for (tmp = mem_heap; tmp->state && tmp->size < size; tmp = tmp->next) {
        if (!tmp) {
            panic("krmalloc fail, not found enough memory.");
        }
    }
    uint32_t save = tmp->size - size - node_size;
    // 这里要注意剩余的空间不够存放Node header的情况
    if (save > 0) {
        tmp->state = 1;
        tmp->size = size;
        uint32_t rnode_ptr = (uint32_t)tmp + size + node_size;
        struct node *rnode = (struct node *)rnode_ptr;
        rnode->state = 0;
        rnode->size = save; // 除去节点头大小后的尺寸
        rnode->next = tmp->next;
        if (tmp->next)
            tmp->next->previous = rnode;
        rnode->previous = tmp;
        tmp->next = rnode;
        return tmp->data;
    } else { // 空间不够存放node header
        tmp->state = 1;
        return tmp->data;
    }
}

void merge_free_node(struct node *lnode, struct node *rnode) {
    uint32_t size = lnode->size + rnode->size + node_size;
    lnode->size = size;
    lnode->state = 0;
    lnode->next = rnode->next;
    rnode->previous = lnode;
};

// 
// fix bug: free后没有还原previous, tmp->previous有错误
void krfree(void *ptr) {
    struct node *tmp = (struct node *)((uint32_t)ptr - node_size);
    tmp->state = 0;
    // 这里要分4种情况，左空闲/占用，中占用，右空闲/占用
    if (tmp->next && !tmp->next->state) { // 右边为空闲
        merge_free_node(tmp, tmp->next);
    }
    if (tmp->previous && !tmp->previous->state) { // 左为空闲
        merge_free_node(tmp->previous, tmp);
    }
}
