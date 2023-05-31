#include <memory.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct fs_node {
    char filename[128];
    uint16_t start_NO;     // 起始簌
    uint16_t length;       // 长度为0，则文件不存在
    uint32_t size;         // 文件大
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

int main() {
    int file_number = 1;
    int fs_size
        = sizeof(struct fs_header) + sizeof(struct fs_node) * file_number;
    struct fs_header *head = (struct fs_header *)malloc(fs_size);
    printf("%d\n", sizeof(*head));
    printf("%d\n", fs_size);
    head->file_number = 1;
    char filename[] = "hello.txt\0";
    memcpy(&head->nodes[0], filename, sizeof(filename));
    head->nodes[0].start_NO = 0;
    head->nodes[0].length = 1;
    head->nodes[0].size = 1;
    FILE *f = fopen("initrd.img", "wb");
    fwrite(head, fs_size, 1, f);
    unsigned char space = '\x00';
    for (int i = fs_size; i < 16 * 1024 * 1024; ++i) {
        fwrite(&space, 1, 1, f);
    }
    fclose(f);
}