#ifndef _ASM_H_
#define _ASM_H_

#include <stdint.h>

extern void outb(uint16_t port, uint8_t value);
extern uint8_t inb(uint16_t port);
extern void exit();

extern void load_idt(uint32_t ldtr);
extern void int_handler();
extern void _cli();
extern void _sti();

#endif