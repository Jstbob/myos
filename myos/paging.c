#include "paging.h"
#include <stdint.h>

/*
 * 分页属性描述符
 * |31 - - - - - 12|11 - 9|8 - 7|6|5|4 - 3| 2 | 1 |0|
 * |physical offset| AVAIL| RSVD|D|A|RSVD |U/S|R/W|P|
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
 *  |   固定区      |
 *  |   内核代码区  |
 *  |   内核堆区    |
 *  |   用户代码区  |   使用 BIOS 中断获取总内存大小/2
 *  |   用户栈区    |
 *  |   内存虚拟硬盘 |  16MB
 */

void init_paging(){

}