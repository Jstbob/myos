#include <stdint.h>

#define IDT_ENTRYS 256
#define IDT_LIMIT (IDT_ENTRYS*8-1) 

struct IDTR{
    const uint16_t IDT_lit = IDT_LIMIT;    // entry count bytes
    uint32_t IDT_base;     // entry head addr
}__attribute__((packed));

// gate descriptor seletor segment descriptor
struct gate_descriptor{
    uint16_t offset_down16;
    uint16_t selector;      // index from gdt
    uint16_t priority;
    uint16_t offset_up16;
}__attribute__((packed));

typedef uint64_t IDT[IDT_ENTRYS];   // define 256's interrupt

struct GDTR{
    uint16_t GDT_limit;     // 32*5-1=
    uint32_t GDT_base;
}__attribute__((packed));

// segment descriptor table, base=0, limit=4G, G=1, D/B=1, P=1, AVL=x/0
// NULL                                                                 
// app code segment descriptor, S=1, DPL=3, type=b1011, X/R/A     0f cf fb 00  00 00 ff ff
// app data segment descriptor, S=1, DPL=3, type=b0011, W/R/A           f3
// system code segment descriptor, S=1, DPL=0, type=b1011, X/R/A        9b
// system data segment descriptor, S=1, DPL=0, type=b0011. W/R/A        93
struct segment_descriptor{
    uint16_t segment_limit;     // ff ff
    uint16_t segment_base;      // 00 00
    uint16_t segment_dpl;       // 00 fb/f3/9b/93
    uint16_t segment_avl;       // cf 0f
}__attribute__((packed));

#define NULL_SEG 0
#define CODE_SEG 0xffff000000fbcf0f
#define DATA_SEG 0xffff000000f3cf0f
#define KDCODE_SEG 0xffff0000009bcf0f
#define KDDATA_SEG 0xffff00000093cf0f

// CR3
// #define PDBR 0x xx xx xx 00 01 80
uint32_t PD[1024];      // 1024's memory directory
uint32_t PT[1024];      // 1024's memory entry
