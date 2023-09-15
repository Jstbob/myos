#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <stdint.h>

/*
 *  word format:
 *      15 ----------- 12 11 ------------- 8 7 ----------- 0
 *         background         foreground        char_code
 */

// 黑底白字
#define COLOR 0x07
// 缓冲区起始地址
#define VIDEO_MEMORY_ADDR 0xB8000
#define WEIGHT 80
#define HIGHT 25

struct console {
    uint16_t cur_pos_x; // 游标x坐标
    uint16_t cur_pos_y; // 游标y坐标
    uint16_t *video_temp;
};

// 测试正常，2023/09/07
void console_init();
void clear_screent();
void console_putchar(uint16_t x, uint16_t y, char chr);
void move_pos(uint16_t x, uint16_t y);
void push_char(char c);
void panic(char *msg);
void push_anum(char a_num); // num必须为0-9
void print_uint32(uint32_t num);
void print_msg(char *msg);

#endif