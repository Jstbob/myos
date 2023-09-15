#include "console.h"
#include "asm.h"
#include <stdint.h>

static struct console video;

void console_init() {
    video.video_temp = (uint16_t *)VIDEO_MEMORY_ADDR;
    clear_screent();
    move_pos(0, 0);
}

void clear_screent() {
    char blank = ' ';
    for (uint16_t i = 0; i < HIGHT; ++i) {
        for (uint16_t j = 0; j < WEIGHT; ++j) {
            console_putchar(j, i, blank);
        }
    }
}

void console_putchar(uint16_t x, uint16_t y, char chr) {
    uint16_t cur_position = x + y * WEIGHT;
    *(video.video_temp + cur_position) = (COLOR << 8) | chr;
}

void move_pos(uint16_t x, uint16_t y) {
    uint16_t cur_position = x + y * WEIGHT;
    // out 14, 0x3D4
    outb(0x3D4, 14);
    outb(0x3D5, cur_position >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cur_position & 0x00ff);
    video.cur_pos_x = x;
    video.cur_pos_y = y;
}

void clear_line(uint16_t y) {
    uint16_t cur_position = y * WEIGHT;
    for (uint16_t i = 0; i < WEIGHT; ++i) {
        video.video_temp[cur_position + i] = ' ';
    }
    move_pos(0, video.cur_pos_y);
}

void srcoll_line() {
    uint16_t cur_position = video.cur_pos_x + video.cur_pos_y * WEIGHT;
    for (uint16_t i = WEIGHT; i < cur_position; ++i) {
        video.video_temp[i - WEIGHT] = video.video_temp[i];
    }
    clear_line(video.cur_pos_y);
}

void enter() {
    video.cur_pos_x = 0;
    if (video.cur_pos_y == HIGHT) {
        srcoll_line();
    } else {
        move_pos(video.cur_pos_x, video.cur_pos_y + 1);
    }
}

// 带自动换行
void push_char(char c) {
    if (c == '\n') {
        enter();
        return;
    }
    if (video.cur_pos_x == WEIGHT) {
        enter();
    }
    console_putchar(video.cur_pos_x, video.cur_pos_y, c);
    move_pos(video.cur_pos_x + 1, video.cur_pos_y);
}

void print_msg(char *msg) {
    while (*msg != '\0') {
        push_char(*msg);
        ++msg;
    }
}

// 测试正常
void panic(char *msg) {
    print_msg(msg);
    exit();
}

// push单个数字
void push_anum(char a_num) {
    a_num += '0';
    push_char(a_num);
}

void print_uint32(uint32_t num) {
    // uint32_t最大有10位
    uint8_t tmp[10];
    for (uint8_t i = 0; i < 10; ++i) {
        tmp[i] = 0;
    }
    uint8_t ff = num;
    uint8_t rem;
    uint8_t i = 0;

    while (ff) {
        ff = num / 10;
        rem = num % 10;
        tmp[i] = rem;
        num = ff;
        ++i;
    }

    if (i == 0) {
        push_anum(tmp[i]);
    } else {
        while (i) {
            --i;
            push_anum(tmp[i]);
        }
    }
}
