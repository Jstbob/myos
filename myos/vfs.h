#ifndef _VFS_H
#define _VFS_H

#include <stdint.h>

// enum { DIRECTORY, FILE };

// /*
//  * 16MB硬盘，每块512Bytes, 16*1024*1024/512=32768
//  * 簌号从1开始，共32768块
//  */
// struct fs_node {
//     uint16_t next_index;
//     char name[128];
//     uint8_t type;
//     uint32_t length;
//     uint16_t array[];   // 子节点的索引
// } __attribute__((packed));

// struct fs_header {

// } __attribute__((packed));

struct fs_node {
    char filename[128];
    uint16_t start_NO;     // 起始簌
    uint16_t length;       // 长度为0，则文件不存在
    uint32_t size;
} __attribute__((packed)); // 字节128+2+2+4=136

struct file_block {
    unsigned char block[512];
} __attribute__((packed));

// 16MB文件，头占512KB，真实文件内存占剩余的15.5MB，簌的总数量为15872，文件EOF字符:4
// 512*1024/136=3971个
struct fs_header {
    uint16_t file_number;
    struct fs_node nodes[];
} __attribute__((packed));

void init_root_node(uint32_t mount_point_addr);
void ls();
void print_first_filename();

#endif