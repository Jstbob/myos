#ifndef _PROCESS_H_
#define _PROCESS_H_

#include "boot.h"
#include "stdint.h"

static uint32_t available_pages;
static uint32_t next_page_index;
void init_available_mem(uint32_t mem_cap);
uint32_t alloc_pages(uint32_t pages);

/* 创建进程：
 * 1. 创建进程时，需要先读取文件的大小，再申请所需的物理内存
 * 2. 复制内核的8个内存目录，再将物理内存映射到逻辑地址空间
 */

struct process {
    uint32_t *pd; // 进程内存分页目录指针
    char name[128];
    char args;
    char argv;
};

// 进程环形链表
struct loop_list {
    struct process *cur_process;
    struct process *next;
};

static struct loop_list lp_list = { .cur_process = 0, .next = 0 };

typedef int (*main_t)(int args, char **argv);
// 切换进程，改变栈的位置，再将栈中保存的数据的复原，再修改eip的位置
void create_process();
void first_process();

#endif