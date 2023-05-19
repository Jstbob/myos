#include "idt.h"
#include "monitor.h"
#include <stdint.h>


struct idt_entry {
    uint16_t base_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_hi
} __attribute__((packed));

struct lidt {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct idt_entry idt_list[256] = { 0 };

void set_idt_entry(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_list[num].base_lo = base & 0xFFFF;
    idt_list[num].base_hi = (base >> 16) & 0xFFFF;

    idt_list[num].sel = sel;
    idt_list[num].always0 = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    idt_list[num].flags = flags /* | 0x60 */;
}

void init_idt() {
    struct lidt idt;
    idt.base = (uint32_t)&idt_list;
    idt.limit = sizeof(struct idt_entry) * 256 - 1;

    set_idt_entry(0, (uint32_t)isr0, 0x08, 0x8E);
    set_idt_entry(1, (uint32_t)isr1, 0x08, 0x8E);
    set_idt_entry(2, (uint32_t)isr2, 0x08, 0x8E);
    set_idt_entry(3, (uint32_t)isr3, 0x08, 0x8E);
    set_idt_entry(4, (uint32_t)isr4, 0x08, 0x8E);
    set_idt_entry(5, (uint32_t)isr5, 0x08, 0x8E);
    set_idt_entry(6, (uint32_t)isr6, 0x08, 0x8E);
    set_idt_entry(7, (uint32_t)isr7, 0x08, 0x8E);
    set_idt_entry(8, (uint32_t)isr8, 0x08, 0x8E);
    set_idt_entry(9, (uint32_t)isr9, 0x08, 0x8E);
    set_idt_entry(10, (uint32_t)isr10, 0x08, 0x8E);
    set_idt_entry(11, (uint32_t)isr11, 0x08, 0x8E);
    set_idt_entry(12, (uint32_t)isr12, 0x08, 0x8E);
    set_idt_entry(13, (uint32_t)isr13, 0x08, 0x8E);
    set_idt_entry(14, (uint32_t)isr14, 0x08, 0x8E);
    set_idt_entry(15, (uint32_t)isr15, 0x08, 0x8E);
    set_idt_entry(16, (uint32_t)isr16, 0x08, 0x8E);
    set_idt_entry(17, (uint32_t)isr17, 0x08, 0x8E);
    set_idt_entry(18, (uint32_t)isr18, 0x08, 0x8E);
    set_idt_entry(19, (uint32_t)isr19, 0x08, 0x8E);
    set_idt_entry(20, (uint32_t)isr20, 0x08, 0x8E);
    set_idt_entry(21, (uint32_t)isr21, 0x08, 0x8E);
    set_idt_entry(22, (uint32_t)isr22, 0x08, 0x8E);
    set_idt_entry(23, (uint32_t)isr23, 0x08, 0x8E);
    set_idt_entry(24, (uint32_t)isr24, 0x08, 0x8E);
    set_idt_entry(25, (uint32_t)isr25, 0x08, 0x8E);
    set_idt_entry(26, (uint32_t)isr26, 0x08, 0x8E);
    set_idt_entry(27, (uint32_t)isr27, 0x08, 0x8E);
    set_idt_entry(28, (uint32_t)isr28, 0x08, 0x8E);
    set_idt_entry(29, (uint32_t)isr29, 0x08, 0x8E);
    set_idt_entry(30, (uint32_t)isr30, 0x08, 0x8E);
    set_idt_entry(31, (uint32_t)isr31, 0x08, 0x8E);

    idt_flush((uint32_t)&idt);
}

void exception_handler(uint32_t err_no) {
    monitor_write("int: ");
    monitor_write_hex(err_no);
    monitor_put('\n');
}
