#ifndef _GDT_H
#define _GDT_H

#include <stdint.h>
void init_gdt();
extern void gdt_flush(uint32_t);

#endif