#include "pic.h"
#include "asm.h"

// 这里remap直接使用osdev的代码
#define PIC1 0x20 /* IO base address for master PIC */
#define PIC2 0xA0 /* IO base address for slave PIC */
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)

/* reinitialize the PIC controllers, giving them specified vector offsets
   rather than 8h and 70h, as configured by default */

#define ICW1_ICW4 0x01      /* Indicates that ICW4 will be present */
#define ICW1_SINGLE 0x02    /* Single (cascade) mode */
#define ICW1_INTERVAL4 0x04 /* Call address interval 4 (8) */
#define ICW1_LEVEL 0x08     /* Level triggered (edge) mode */
#define ICW1_INIT 0x10      /* Initialization - required! */

#define ICW4_8086 0x01       /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO 0x02       /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE 0x08  /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C /* Buffered mode/master */
#define ICW4_SFNM 0x10       /* Special fully nested (not) */

/*
arguments:
    offset1 - vector offset for master PIC
        vectors on the master become offset1..offset1+7
    offset2 - same for slave PIC: offset2..offset2+7
*/
void PIC_remap(int offset1, int offset2) {
    unsigned char a1, a2;

    a1 = inb(PIC1_DATA); // save masks
    a2 = inb(PIC2_DATA);

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); // starts the initialization
                                               // sequence (in cascade mode)

    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

    outb(PIC1_DATA, offset1); // ICW2: Master PIC vector offset

    outb(PIC2_DATA, offset2); // ICW2: Slave PIC vector offset

    outb(PIC1_DATA, 4); // ICW3: tell Master PIC that there is a slave PIC at
                        // IRQ2 (0000 0100)

    outb(PIC2_DATA,
         2); // ICW3: tell Slave PIC its cascade identity (0000 0010)

    outb(PIC1_DATA,
         ICW4_8086); // ICW4: have the PICs use 8086 mode (and not 8080 mode)

    outb(PIC2_DATA, ICW4_8086);

    outb(PIC1_DATA, a1); // restore saved masks.
    outb(PIC2_DATA, a2);
}

void rmap_pic(){
    outb(0x21,0xff);
    outb(0xA1,0xff);

    outb(0x20,0x11);
    outb(0x21,0x20);
    outb(0x21,1<<2);
    outb(0x21,0x01);

    outb(0xA0,0x11);
    outb(0xA1,0x20);
    outb(0xA1,1<<2);
    outb(0xA1,0x01);

    outb(0x21,0xfd);    // 屏蔽IRQ0、1此外的中断
    outb(0xA1,0xff);
}

void init_pic() {
    _cli();
    // 将主、从分别映射到0x20、0x28，实际的中断号响应为32-47。
    // PIC_remap(0x20, 0x28);
    rmap_pic();
    // init_timer(200);
    _sti();
}

// 中断发生后，每次都需要重置PIC
void handler_reset(uint32_t code) {
    if (code >= 40) {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);
}

void init_timer(uint32_t ticker) {
    uint16_t count = 1.19318 * ticker;
    uint8_t lo = count & 0xff;
    uint8_t hi = count >> 8;
    outb(0x43, 0x36);
    outb(0x40, lo);
    outb(0x40, hi);
}
