#include "gdt.h"
#include <stdint.h>

struct gdt_entry {
    uint16_t limit_low;  // The lower 16 bits of the limit.
    uint16_t base_low;   // The lower 16 bits of the base.
    uint8_t base_middle; // The next 8 bits of the base.
    uint8_t access; // Access flags, determine what ring this segment can be
                    // used in.
    uint8_t granularity;
    uint8_t base_high; // The last 8 bits of the base.
} __attribute__((packed));

struct ldtr {
    uint16_t limit; // The upper 16 bits of all selector limits.
    uint32_t base;  // The address of the first gdt_entry_t struct.
} __attribute__((packed));

struct gdt_entry gdt_list[5];

void set_gdt_entry(uint8_t num, uint32_t base, uint32_t limit, uint8_t access,
                   uint8_t gran) {
    gdt_list[num].base_low = (base & 0xFFFF);
    gdt_list[num].base_middle = (base >> 16) & 0xFF;
    gdt_list[num].base_high = (base >> 24) & 0xFF;

    gdt_list[num].limit_low = (limit & 0xFFFF);
    gdt_list[num].granularity = (limit >> 16) & 0x0F;

    gdt_list[num].granularity |= gran & 0xF0;
    gdt_list[num].access = access;
}

/* 填充表
 * 填充lgtr
 * 加载lgtr
 * 设置段寄存器的值
 */
void init_gdt() {
    struct ldtr gdt_ldtr;
    gdt_ldtr.base = (uint32_t)&gdt_list;
    gdt_ldtr.limit = (sizeof(struct gdt_entry) * 5) - 1;

    set_gdt_entry(0, 0, 0, 0, 0);
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    set_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    set_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    gdt_flush((uint32_t)&gdt_ldtr);
}