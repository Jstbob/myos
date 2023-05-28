#include "descriptor_tables.h"
#include "common.h"
#include "monitor.h"
#include <stdint.h>

/**
 * 段描述符是个8字节结构体，查看intel白皮书3卷3.4.5
 * 可以查看结构体的位定义，描述符表是描述符的列表
 */

struct segment_descriptor {
    uint16_t limit_low;  // segment limit 15:00, 低16
    uint16_t base_low;   // segment base 15:00，低16
    uint8_t base_middle; // segment base 23:16，中8
    uint8_t access; // Access flags, determine what ring this segment can be
                    // used in.
    uint8_t
        granularity;   // The granularity byte, which contains flags that
                       // describe the segment's size and unit of measurement.
    uint8_t base_high; // segment base 31:24，高8
} __attribute__((packed));

static struct segment_descriptor global_descriptor_tables[5];
static struct gdt_ptr_t gdt_ptr;

static void register_gdt(uint16_t index, uint32_t base, uint32_t limit,
                         uint8_t access, uint8_t granularity);
static void gdt_flush(uint32_t gdt_ptr);
static void init_idt();

void init_descriptor_tables() {
    gdt_ptr.limit = (sizeof(global_descriptor_tables) * 5) - 1;
    gdt_ptr.base = (uint32_t)&global_descriptor_tables;

    register_gdt(0, 0, 0, 0, 0);                // Null segment
    register_gdt(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    register_gdt(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    register_gdt(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    register_gdt(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    gdt_flush((uint32_t)&gdt_ptr);
    init_idt();
}

static void register_gdt(uint16_t index, uint32_t base, uint32_t limit,
                         uint8_t access, uint8_t granularity) {
    global_descriptor_tables[index].base_low = base & 0xFFFF;
    global_descriptor_tables[index].base_middle = (base >> 16) & 0xFF;
    global_descriptor_tables[index].base_high = (base >> 24) & 0xFF;

    global_descriptor_tables[index].limit_low = limit & 0xFFFF;

    global_descriptor_tables[index].granularity = (limit >> 16) & 0x0F;
    global_descriptor_tables[index].granularity |= granularity & 0xF0;

    global_descriptor_tables[index].access = access;
}

static void gdt_flush(uint32_t gdt_ptr) {
    asm volatile("lgdt (%%eax);"
                 "mov $0x10, %%ax;"
                 "mov %%ax, %%ds;"
                 "mov %%ax, %%ds;"
                 "mov %%ax, %%ds;"
                 "mov %%ax, %%ds;"
                 "mov %%ax, %%ds;"
                 "ljmp $0x08, $flush;"
                 "flush:;" ::"a"(gdt_ptr)
                 :);
}

/*
 * idt 中断描述符表，总有 256 个条目；
 * 用途：用来处理 interrupts 和 IRQs；
 * CPU 内部中断号：
 * 0 - Division by zero exception
 * 1 - Debug exception
 * 2 - Non maskable interrupt
 * 3 - Breakpoint exception
 * 4 - 'Into detected overflow'
 * 5 - Out of bounds exception
 * 6 - Invalid opcode exception
 * 7 - No coprocessor exception
 * 8 - Double fault (pushes an error code)
 * 9 - Coprocessor segment overrun
 * 10 - Bad TSS (pushes an error code)
 * 11 - Segment not present (pushes an error code)
 * 12 - Stack fault (pushes an error code)
 * 13 - General protection fault (pushes an error code)
 * 14 - Page fault (pushes an error code)
 * 15 - Unknown interrupt exception
 * 16 - Coprocessor fault
 * 17 - Alignment check exception
 * 18 - Machine check exception
 * 19-31 - Reserved
 * 中断 8、10-14 ，CPU会自动将错误代码压入栈，其他的需要压虚拟错误码。
 */

struct idt_entry_t {
    uint16_t offset_low;  // 中断处理程序的低16位
    uint16_t selector;    // 处理程序所在的代码段选择符
    uint8_t zero;         // 保留字段，通常总为0
    uint8_t flags;        // IDT条目的特定属性
    uint16_t offset_high; // 中断处理程序的高16位
} __attribute__((packed));

struct idt_entry_t idt_entries[256];
struct idt_ptr_t idt_ptr;
idt_call_back idt_tables[256];

static void idt_flush(uint32_t ptr);
static void idt_call_back_fun(struct registers_t *regs);

static void init_idt() {
    idt_ptr.limit = sizeof(struct idt_entry_t) * 256 - 1;
    idt_ptr.base = (uint32_t)&idt_entries;

    register_idt(0, (uint32_t)&isr0, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(1, (uint32_t)&isr1, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(2, (uint32_t)&isr2, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(3, (uint32_t)&isr3, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(4, (uint32_t)&isr4, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(5, (uint32_t)&isr5, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(6, (uint32_t)&isr6, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(7, (uint32_t)&isr7, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(8, (uint32_t)&isr8, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(9, (uint32_t)&isr9, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(10, (uint32_t)&isr10, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(11, (uint32_t)&isr11, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(12, (uint32_t)&isr12, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(13, (uint32_t)&isr13, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(14, (uint32_t)&isr14, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(15, (uint32_t)&isr15, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(16, (uint32_t)&isr16, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(17, (uint32_t)&isr17, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(18, (uint32_t)&isr18, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(19, (uint32_t)&isr19, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(20, (uint32_t)&isr20, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(21, (uint32_t)&isr21, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(22, (uint32_t)&isr22, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(23, (uint32_t)&isr23, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(24, (uint32_t)&isr24, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(25, (uint32_t)&isr25, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(26, (uint32_t)&isr26, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(27, (uint32_t)&isr27, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(28, (uint32_t)&isr28, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(29, (uint32_t)&isr29, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(30, (uint32_t)&isr30, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(31, (uint32_t)&isr31, 0x08, 0x8E, &idt_call_back_fun);

    idt_flush((uint32_t)&idt_ptr);
}

// 注册idt的回调函数
void register_idt(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags,
                  idt_call_back idt_call_back_fun) {
    idt_entries[num].offset_low = base & 0xFFFF;
    idt_entries[num].offset_high = (base >> 16) & 0xFFFF;

    idt_entries[num].selector = selector;
    idt_entries[num].zero = 0;
    // We must uncomment the OR below when we get to using user-mode.
    // It sets the interrupt gate's privilege level to 3.
    idt_entries[num].flags = flags /* | 0x60 */;

    idt_tables[num] = idt_call_back_fun;
}

static void idt_flush(uint32_t ptr) {
    asm volatile("lidt (%%eax);" ::"a"(ptr) :);
}

static void idt_call_back_fun(struct registers_t *regs) {
    uint32_t int_no = regs->int_no;
    monitor_write_msg("int_no: ");
    monitor_write_hex((char *)&int_no, sizeof(int_no));
    enter_new_line();
}

void idt_disatch(struct registers_t regs) {
    idt_call_back fun = idt_tables[regs.int_no];
    fun(&regs);
}

static void init_timer();

void init_iqr() {
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    init_timer(); // IRQ0被定时器使用
    register_idt(33, (uint32_t)&irq1, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(34, (uint32_t)&irq2, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(35, (uint32_t)&irq3, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(36, (uint32_t)&irq4, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(37, (uint32_t)&irq5, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(38, (uint32_t)&irq6, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(39, (uint32_t)&irq7, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(40, (uint32_t)&irq8, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(41, (uint32_t)&irq9, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(42, (uint32_t)&irq10, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(43, (uint32_t)&irq11, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(44, (uint32_t)&irq12, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(45, (uint32_t)&irq13, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(46, (uint32_t)&irq14, 0x08, 0x8E, &idt_call_back_fun);
    register_idt(47, (uint32_t)&irq15, 0x08, 0x8E, &idt_call_back_fun);
}

/*
 * PIC定时器控制器是在IRQ0中断，需要定制IRQ0的handler的程序
 */

static uint32_t tick = 0;

static void timer_call_back(struct registers_t *regs) {
    if (regs->int_no >= 40) {
        // Send reset signal to slave.
        outb(0xA0, 0x20);
    }
    // Send reset signal to master. (As well as slave, if necessary).
    outb(0x20, 0x20);

    tick++;
    monitor_write_msg("Tick: ");
    monitor_write_hex((char *)&tick, sizeof(tick));
    enter_new_line();
}

static void init_timer() {
    asm volatile("cli");
    register_idt(32, (uint32_t)&irq0, 0x08, 0x8E, &timer_call_back);
    uint32_t divisor = 1193180 / 50;
    outb(0x43, 0x36);
    uint8_t l = (uint8_t)(divisor & 0xFF);
    uint8_t h = (uint8_t)((divisor >> 8) & 0xFF);
    outb(0x40, l);
    outb(0x40, h);
    asm volatile("sti");
}
