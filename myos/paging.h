#ifndef _PAGING_H
#define _PAGING_H

#include <stdint.h>
#include "common.h"
#include "descriptor_tables.h"

/*
 * |31 - - - - - 12|11 - 9|8 - 7|6|5|4 - 3| 2 | 1 |0|
 * |physical offset| AVAIL| RSVD|D|A|RSVD |U/S|R/W|P|
 *                        (11)2
 */ 

void init_paging();

#endif