#ifndef _MONITOR_H
#define _MONITOR_H

#include <stdint.h>

void init_monitor(); // 清屏

void monitor_write_char(char c);
void move_cursor(uint16_t x, uint16_t y);
void enter_new_line();
void monitor_write_msg(const char *str);
void monitor_write_hex(char *p, uint32_t length);
void monitor_print_msg(const char *msg, uint32_t size);

#endif