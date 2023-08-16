#include "common.h"
#include "monitor.h"
#include <stdint.h>

void outb(uint16_t port, uint8_t value) {
    asm volatile("outb %1, %0" : : "dN"(port), "a"(value));
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

uint16_t inw(uint16_t port) {
    uint16_t ret;
    asm volatile("inw %1, %0" : "=a"(ret) : "dN"(port));
    return ret;
}

void panic(const char *message, const char *file, uint32_t line) {
    // We encountered a massive problem and have to stop.
    asm volatile("cli"); // Disable interrupts.

    monitor_write_msg("PANIC(");
    monitor_write_msg(message);
    monitor_write_msg(") at ");
    monitor_write_msg(file);
    monitor_write_msg(":");
    monitor_write_hex((char *)&line, sizeof(line));
    monitor_write_msg("\n");
    // Halt by going into an infinite loop.
    while (1)
        ;
}

// Write len copies of val into dest.
void memset(uint8_t *dest, uint8_t val, uint32_t len) {
    uint8_t *temp = (uint8_t *)dest;
    for (; len != 0; len--)
        *temp++ = val;
}