#ifndef _PIC_H_
#define _PIC_H_

#include <stdint.h>

void init_pic(); // 初始化8259PIC
void handler_reset(uint32_t code);

// 初始化定时器，ticker为每个多少us时间发送一次中断
void init_timer(uint32_t ticker);

#endif