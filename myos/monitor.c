#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define WIDE 80
#define HIGH 25
#define TEXT_BUFFER_ADDRESS 0xB8000
#define COLOR 0x0f // 黑底白字

extern void _asm_set_pos(uint16_t);
extern void _kernel_main(void);

struct monitor {
    uint16_t (*data)[WIDE];
    uint16_t cursor_x;
    uint16_t cursor_y;
};

uint16_t to_char16(char c) {
    return (COLOR << 8) | c;
}

void monitor_set_cursor(struct monitor *m_obj) {
    uint16_t index = m_obj->cursor_x * 80 + m_obj->cursor_y;
    _asm_set_pos(index);
}

void monitor_scroll(struct monitor *m_obj) {
    for (uint16_t i = 1; i < HIGH - 1; ++i) {
        for (uint16_t j = 0; j < WIDE - 1; ++j) {
            m_obj->data[i][j] = m_obj->data[i - 1][j];
        }
    }

    for (uint16_t i = 0; i < WIDE - 1; ++i) {
        m_obj->data[HIGH - 1][i] = to_char16(0);
    }
}

void monitor_putc(struct monitor *m_obj, uint16_t x, uint16_t y, char c) {
    uint16_t simple_c = to_char16(c);
    m_obj->data[x][y] = simple_c;

    ++m_obj->cursor_x;
    if (m_obj->cursor_x > WIDE - 1) {
        ++m_obj->cursor_y;
        m_obj->cursor_x %= WIDE;
    }

    ++m_obj->cursor_y;
    if (m_obj->cursor_y >= HIGH - 1) {
        monitor_scroll(m_obj);
    }
    monitor_set_cursor(m_obj);
}

void monitor_cursor_zero(struct monitor *m_obj){
    m_obj->cursor_x = m_obj->cursor_y = 0;
    monitor_set_cursor(m_obj);
}

void monitor_init(struct monitor *m_obj) {
    monitor_cursor_zero(m_obj);
    m_obj->data = (uint16_t(*)[WIDE])TEXT_BUFFER_ADDRESS;
    for (uint16_t x = 0; x < HIGH; ++x) {
        for (uint16_t y = 0; y < WIDE; ++y) {
            monitor_putc(m_obj, x, y, 0);
        }
    }
    monitor_cursor_zero(m_obj);
}

void _kernel_main() {
    struct monitor m_obj;
    monitor_init(&m_obj);
    char msg[] = "hello";
    for (int i = 0; i < sizeof(msg) - 1; ++i) {
        monitor_putc(&m_obj, 0, i, msg[i]);
    }
}