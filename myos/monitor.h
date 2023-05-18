#ifndef _MONITOR_H
#define _MONITOR_H

#include <stdint.h>

static uint16_t *const VIDEO_BASE_ADDR = (uint16_t *)0xB8000;
static const uint16_t COLOR = 0x0F;
static const uint16_t HIGHT = 25;
static const uint16_t WIDE = 80;
static const uint16_t BLANK = (COLOR << 8) | 0x20;

struct monitor {
    uint16_t cursor_x;
    uint16_t cursor_y;
    uint16_t *video_memory;
};

void monitor_init(struct monitor *);

void monitor_putc(struct monitor *, char);

void monitor_clear(struct monitor *);

void monitor_write(struct monitor *, const char *);

static void monitor_move_cursor(struct monitor *);

static void monitor_scroll(struct monitor *);

#endif