#ifndef _BOOT_H_
#define _BOOT_H_

// 假定内核所占物理内存的大小为32MB，占用8个页目录
#define KERNEL_MEMORY (1024 * 1024 * 32)
#define KERNEL_PDS 8

#define PD_COUNT 1024
#define PT_COUNT 1024
// 总的分页个数
#define KERNEL_PAGE_ENTRIES (PD_COUNT * PT_COUNT)
#define PAGE_ATTR 0x07

/*
 * ref intel spec 3, page entry define:
 *      31-12   base_addr: pt front 22 bit
 *      11-9    Avail: 0
 *      8       G: 0
 *      7       PS/PAT: 0
 *      6       D: 0
 *      5       A: 0
 *      4       PCD: 0
 *      3       PWT: 0
 *      2       U/S: kernel = 1, user = 0
 *      1       R/W: enble R/W = 1, enble only R = 0;
 *      0       P:  1 = exits memory, 0 = no exits memory
 *      gen: 0 | (1 << 2 ) | (1 << 1) | 1
 *      base_addr | 0x7
 */

 /*
  * segment descriptor:
  *     type, base, limit, dpl
  *     (base&0xff)<<32 | base , todo
  *     0x00, , , 0x00
  *     0x00, , , 
  * 可以拆分成8个字节构建:
  * 第一字节0x00，第二字节0xcf，第三字节0x90|DPL<<5|TYPE, 第四字节0x00
  * 第五字节0x00，第六字节0x00，第七字节0xff，第八字节0xff
  * DPL为0、3，TYPE为3、b
  * NULL段
  * 内核代码段：DPL=0，TYPE=3，0x90|0x0<<5|0xb=0x9b
  * 内核数据段：DPL=0，TYPE=b，0x90|0x0<<5|0x3=0x93
  * 应用代码段：DPL=3，TYPE=3，0x90|0x3<<5|0xb=0xfb
  * 应用数据段：DPL=0，TYPE=b，0x90|0x0<<5|0x3=0xf3
  * 选择子：
  *     0x00, 0x00
  *     0x00, 0x08
  *     0x00, 0x10
  *     0x00, 0x18
  *     0x00, 0x20
  */

#define SEG(FLAGS)  ((0xcf<<48)|(FLAGS<<40)|0xffff)
#define NULL_SEG    0
#define KCODE_SEG   SEG(0x9a)
#define KDATA_SEG   SEG(0x92)
#define UCODE_SEG   SEG(0xfa)
#define UDATA_SEG   SEG(0xf2)

#endif