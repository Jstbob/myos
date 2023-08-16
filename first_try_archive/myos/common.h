#ifndef _COMMON_h
#define _COMMON_h

#include <stdint.h>

#define NULL 0

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

void panic(const char *message, const char *file, uint32_t line);

void memset(uint8_t *dest, uint8_t val, uint32_t len);

#endif