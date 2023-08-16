#include "descriptor_tables.h"
#include "monitor.h"
#include "paging.h"
#include <assert.h>
#include <stdint.h>

static void test_monitor_main();
static void test_intterupt();
static void test_timer();
static void test_paging();

void test_main() {
    // test_monitor_main();
    // test_intterupt();
    // test_timer();
    test_paging();
}

static void test_monitor_write_msg() {
    char msg[] = "helloworld";
    for (int i = 0; i < sizeof(msg) - 1; ++i) {
        monitor_write_char(msg[i]);
    }
}

// test monitor is pass
static void test_monitor_main() {
    init_monitor();
    for (int i = 0; i < 25; ++i) {
        monitor_write_char('\n');
    }
    test_monitor_write_msg();
    enter_new_line();
    monitor_write_char('\n');
    test_monitor_write_msg();
    enter_new_line();

    uint32_t numb = 0x1f2f3f4f;
    monitor_write_hex((char *)&numb, sizeof(numb));
}

static struct gdt_ptr_t l_gdt_ptr;
static struct idt_ptr_t l_idt_ptr;

static void print_gdt() {
    asm volatile("sgdt (%%eax);" ::"a"(&l_gdt_ptr) :);
    uint32_t base_ptr = l_gdt_ptr.base;
    monitor_write_hex((char *)&base_ptr, sizeof(base_ptr));
    enter_new_line();
}

static void print_idt() {
    asm volatile("sidt (%%eax);" ::"a"(&l_idt_ptr) :);
    uint32_t base_ptr = l_idt_ptr.base;
    monitor_write_hex((char *)&base_ptr, sizeof(base_ptr));
    enter_new_line();
}

// test is pass
static void test_intterupt() {
    init_monitor();
    init_descriptor_tables();
    test_monitor_write_msg();

    print_gdt();
    print_idt();

    // asm volatile("int $8;");
    asm volatile("int $4;");
    asm volatile("int $5;");
};

static void test_timer() {
    init_monitor();
    init_descriptor_tables();
    init_irq();
    asm volatile("int $4;");
    asm volatile("int $34;");
    asm volatile("int $32;");
    while (1)
        ;
}

static void test_paging() {
    init_monitor();
    init_descriptor_tables();
    init_paging();
    uint32_t *ptr = (uint32_t *)0x80000000;
    *ptr = 20;
    uint32_t *u_ptr = (uint32_t *)0xf0000000;
    *u_ptr = 20;
    while (1)
        ;
}

// static void test_paging() {
//     init_monitor();
//     init_descriptor_tables();
//     initialise_paging();
//     uint32_t *ptr = (uint32_t *)0x100000000;
//     *ptr = 20;
//     uint32_t *u_ptr = (uint32_t *)0xf0000000;
//     *u_ptr = 20;
//     while (1)
//         ;
// }