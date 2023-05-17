#include <stddef.h>
#include <stdint.h>

extern void asm_set_pos(uint16_t);

uint16_t *const buff = (uint16_t *)0xB8000;
const uint16_t WIDE = 80;
const uint16_t HEIHT = 25;
uint16_t cur_x = 0;
uint16_t cur_y = 0;
unsigned char DISPLAY_MODE = 0x0f;

uint16_t to_char16(char c) {
    return (DISPLAY_MODE << 8) | c;
}

void set_pos(uint16_t x, uint16_t y) {
    cur_x = 0;
    cur_y = 0;
    asm_set_pos(y * 80 + x);
}

/**
 * @brief 向屏幕（x, y）位置设置字符
 *
 * @param x
 * @param y
 * @param c
 */
void screen_putc(uint16_t x, uint16_t y, char c) {
    uint16_t index = 80 * y + x;
    buff[index] = to_char16(c);
    ++x;
    if (x > WIDE) { // 换行
        ++y;
        x -= WIDE;
    }
    ++y;
    set_pos(x, y);
}

void screen_clear() {
    for (uint16_t i = 0; i < 25; ++i) {
        for (uint16_t j = 0; j < 80; ++j) {
            screen_putc(j, i, 0);
        }
    }
    set_pos(0, 0);
}

void kernel_main() {
    char msg[] = "hello";
    screen_clear();
    for (uint16_t i = 0; i < sizeof(msg) - 1; ++i) {
        screen_putc(i, 0, msg[i]);
    }
}