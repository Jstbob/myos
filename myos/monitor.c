#include "monitor.h"
#include "common.h"
#include <stdint.h>

/* 屏幕黑白模式下，缓冲区由 80x25 个 chat16组成;
 *
 * 每个chat16的位属性:
 *  |15 - - - - - - - 12|11 - - - - - - - 8|7 - - - - - - 0|
 *  |Background colour  |Foreground colour |Character code |
 *
 * 其中，15-12位：背景色，11-8位：前景色，7-0位：ASCII码；
 *
 * 缓冲区起始地址 0xB8000；
 */

#define SPACE_CHAR 0x20        // 清除为空格字符
#define BACK_COLOR 0x0F        // 黑底白字
#define MONITOR_BUFFER 0xB8000 // 缓冲区起始地址
#define BUFFER_WIDTH 80        // 缓冲区宽度
#define BUFFER_HIGHT 25        // 缓冲区高度

static uint16_t *monitor_buffer = (uint16_t *)MONITOR_BUFFER;
static uint16_t cursor_x = 0;
static uint16_t cursor_y = 0;

static uint16_t convert_index(uint16_t x, uint16_t y);
static void scroll(uint16_t raws);
static uint16_t to_char16(char c);

/**
 * @brief 将屏幕清除为空格
 */
void init_monitor() {
    for (uint16_t i = 0; i < BUFFER_HIGHT; ++i) {
        for (uint16_t j = 0; j < BUFFER_WIDTH; ++j) { // 先遍历行可以提高性能
            uint16_t index = convert_index(j, i);
            monitor_buffer[index] = to_char16(SPACE_CHAR);
        }
    }
    move_cursor(0, 0);
}

void monitor_write_char(char c) {
    if (c == '\n') {
        enter_new_line();
    } else {
        if (cursor_x >= BUFFER_WIDTH - 1) { // 超过宽度，先换行再写入字符
            enter_new_line(); // 换行会导致当前游标 x,y 变化
        }
        uint16_t index = convert_index(cursor_x, cursor_y);
        monitor_buffer[index] = to_char16(c);
        ++cursor_x;
        move_cursor(cursor_x, cursor_y);
    }
}

void move_cursor(uint16_t x, uint16_t y) {
    uint16_t index = convert_index(x, y);
    outb(0x3D4, 14);
    outb(0x3D5, index >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, index & 0x00ff);
    cursor_x = x;
    cursor_y = y;
}

static uint16_t convert_index(uint16_t x, uint16_t y) {
    uint16_t index = y * BUFFER_WIDTH + x;
    return index;
}

void enter_new_line() { // 换行
    ++cursor_y;
    cursor_x = 0;
    if (cursor_y >= BUFFER_HIGHT) {
        scroll(1);
    } else {
        move_cursor(cursor_x, cursor_y);
    }
}

static void scroll(uint16_t raws) {
    cursor_y -= raws;
    for (uint16_t i = BUFFER_WIDTH; i < BUFFER_HIGHT * BUFFER_WIDTH; ++i) {
        monitor_buffer[i - BUFFER_WIDTH] = monitor_buffer[i];
    }
    for (uint16_t i = cursor_y * BUFFER_WIDTH; i < BUFFER_HIGHT * BUFFER_WIDTH;
         ++i) {
        monitor_buffer[i] = to_char16(SPACE_CHAR);
    }
    move_cursor(cursor_x, cursor_y);
}

static uint16_t to_char16(char c) {
    uint16_t c_char16 = (BACK_COLOR << 8) | c;
    return c_char16;
}

void monitor_write_msg(const char *str) {
    for (const char *ptr = str; (*ptr) != '\0'; ++ptr) {
        monitor_write_char(*ptr);
    }
}

static char numb2char_16(char numb);

// 反向打印16进制
void monitor_write_hex(char *p, uint32_t length) {
    char c;
    monitor_write_char('0');
    monitor_write_char('x');
    for (int i = length - 1; i >= 0; --i) {
        if (*(p + i) == 0)
            continue;

        char hex16_hight = (*(p + i) >> 4) & 0x0F; // 获取高4位的数值
        c = numb2char_16(hex16_hight);
        monitor_write_char(c);

        char hex16_low = *(p + i) & 0x0F;
        c = numb2char_16(hex16_low);
        monitor_write_char(c);
    }
}

// 将数字映射成16进制的字符
static char numb2char_16(char numb) {
    char c;
    if (numb <= 9) {
        c = numb + 0x30;
    } else {
        c = numb - 0x0A + 0x61;
    }
    return c;
}
