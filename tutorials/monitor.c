#include "monitor.h"
#include "common.h"
#include <stddef.h>
#include <stdint.h>

void monitor_init(struct monitor *m_obj) {
    m_obj->cursor_x = m_obj->cursor_y = 0;
    m_obj->video_memory = VIDEO_BASE_ADDR;
    monitor_clear(m_obj);
    monitor_move_cursor(m_obj);
}

void monitor_clear(struct monitor *m_obj) {
    for (uint16_t i = 0; i < WIDE * HIGHT; ++i) {
        m_obj->video_memory[i] = BLANK;
    }
}

static void monitor_move_cursor(struct monitor *m_obj) {
    uint16_t cursorLocation = m_obj->cursor_y * 80 + m_obj->cursor_x;
    outb(0x3D4, 14);
    outb(0x3D5, cursorLocation >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursorLocation);
}

static void monitor_scroll(struct monitor *m_obj) {
    if (m_obj->cursor_y > HIGHT - 1) {
        for (uint16_t i = 0; i < WIDE * (HIGHT - 1); ++i) {
            m_obj->video_memory[i] = m_obj->video_memory[i + WIDE];
        }

        for (uint16_t i = WIDE * (HIGHT - 1); i < WIDE * HIGHT; ++i) {
            m_obj->video_memory[i] = BLANK;
        }
        m_obj->cursor_y = HIGHT - 1;
        monitor_move_cursor(m_obj);
    }
}

void monitor_putc(struct monitor *m_obj, char c) {
    uint16_t cursorLocation = m_obj->cursor_y * 80 + m_obj->cursor_x;
    m_obj->video_memory[cursorLocation] = (COLOR << 8) | c;
    ++m_obj->cursor_x;
    if (m_obj->cursor_x >= WIDE) {
        ++m_obj->cursor_y;
        m_obj->cursor_x = 0;
        monitor_scroll(m_obj);
    }
    monitor_move_cursor(m_obj);
}

void monitor_write(struct monitor *m_obj, const char *msg) {
    for (const char *p = msg; *p != '\x0'; ++p) {
        monitor_putc(m_obj, *p);
    }
}