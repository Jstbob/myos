#ifndef _DESCRIPTOR_TABLES_H
#define _DESCRIPTOR_TABLES_H

#include <stdint.h>

// GDT Entry struct
struct gdt_entry_t {
    uint8_t base_high;
    uint8_t granularity; // limit_seg high
    uint8_t access;
    uint8_t base_middle;
    uint16_t base_low;
    uint16_t limit_low;
};

struct gdt_ptr_t {
    uint16_t limit; // base + limit 指向 GDT 的最后一个条目
    uint32_t base;  // 指向 GDT
};

struct idt_entry_t {
    uint16_t base_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_hi;
};

struct idt_ptr_t {
    uint16_t limit;
    uint32_t base;
};

extern void gdt_flush(uint32_t);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif