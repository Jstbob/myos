#ifndef _PROCESS_H_
#define _PROCESS_H_

#include "stdint.h"

/*
 * 1. 创建进程时，需要先读取文件的大小，再申请所需的物理内存
 * 2. 复制内核的8个内存目录，再将物理内存映射到逻辑地址空间
 */

struct process {
    uint32_t *pd; // 进程内存分页目录指针
    uint32_t *stack_base;
    uint32_t stack_size;
};

// 进程环形链表
struct loop_list {
    struct process *cur_process;
    struct process *next;
};

// 切换进程
// 改变栈的位置，再将栈中保存的数据的复原，再修改eip的位置
void switch_process();

#endif