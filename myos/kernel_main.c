// main.c -- Defines the C-code kernel entry point, calls initialisation
// routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "gdt.h"
#include "idt.h"
#include "monitor.h"
#include "paging.h"
#include <stdint.h>

typedef struct multiboot_info {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;
    uint32_t num;
    uint32_t size;
    uint32_t addr;
    uint32_t shndx;
    uint32_t mmap_length;
    uint32_t mmap_addr;
    uint32_t drives_length;
    uint32_t drives_addr;
    uint32_t config_table;
    uint32_t boot_loader_name;
    uint32_t apm_table;
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint32_t vbe_mode;
    uint32_t vbe_interface_seg;
    uint32_t vbe_interface_off;
    uint32_t vbe_interface_len;
} multiboot_info_t;

void test_interrupt() {
    monitor_clear();
    monitor_write("Hello, world!\n");
    init_gdt();
    init_idt();
    asm volatile("sti");

    asm volatile("int $0");
    asm volatile("int $1");
    asm volatile("int $2");
    asm volatile("int $3");
    asm volatile("int $4");
    asm volatile("int $5");
    asm volatile("int $6");
    asm volatile("int $7");
    asm volatile("int $8");
    asm volatile("int $9");
    asm volatile("int $10");
    asm volatile("int $11");
    asm volatile("int $12");
    asm volatile("int $13");
    asm volatile("int $14");
    asm volatile("int $15");
    asm volatile("int $16");
    asm volatile("int $17");
    asm volatile("int $18");
    asm volatile("int $19");
    asm volatile("int $20");
    asm volatile("int $21");
    asm volatile("int $22");
    asm volatile("int $23");
    asm volatile("int $24");
    asm volatile("int $25");
    asm volatile("int $26");
    asm volatile("int $27");
    asm volatile("int $28");
    asm volatile("int $29");
    asm volatile("int $30");
    asm volatile("int $31");
}

void test_timer() {
    monitor_clear();
    monitor_write("Hello, world!\n");
    init_gdt();
    init_idt();
    asm volatile("sti");
    init_timer(50);
}

void kernel_main(struct multiboot_info *mboot_ptr) {
    monitor_clear();
    monitor_write("Hello, world!\n");
    init_gdt();
    init_idt();
    init_paging();
    asm volatile("sti");
    uint32_t ptr = 0x80000000;
    uint32_t *n = (uint32_t *)ptr;
    monitor_write_dec(*n);
}
