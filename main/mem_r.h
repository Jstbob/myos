#ifndef _MEM_R_H_
#define _MEM_R_H_

#include "stdint.h"

// 这里遇到了不少坑，固定用法，必须使用char[]这样的类型，才能引用link.ld链接脚本中的变量
extern unsigned char heap_start[];
static uint32_t heap_size;

struct [[gnu::packed]] node {
    uint32_t size;
    uint8_t state; // 0为空闲，1为占用
    struct node *previous;
    struct node *next;
    unsigned char data[];
};

static struct node *mem_heap;
static uint8_t node_size = sizeof(struct node);

void init_mem_heap();
void *krmalloc(uint32_t size);
void krfree(void *ptr);

void mem_cpy(void *src, void *des, uint32_t size);
void mem_set(void *src, uint32_t size, unsigned char c);

#endif