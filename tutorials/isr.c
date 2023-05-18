#include "common.h"
#include "monitor.h"
#include <stdint.h>

struct registers_t {
    uint32_t ds;                                     // Data segment selector
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    uint32_t int_no,
        err_code; // Interrupt number and error code (if applicable)
    uint32_t eip, cs, eflags, useresp,
        ss; // Pushed by the processor automatically.
};

struct monitor m;

void isr_handler(struct registers_t regs) {
    monitor_write(&m, "interrupt: ");
    monitor_putc(&m, regs.int_no + '0');
}

void kernel_main() {
    monitor_init(&m);
    char *msg = "helloworld\n";
    monitor_write(&m, msg);

    asm volatile("int $0x3");
    asm volatile("int $0x4");
}