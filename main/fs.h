#ifndef _FS_H_
#define _FS_H_

#include <stdint.h>

void init_fs();

#define MODE_READ 0
#define MODE_WRITE 1

void rw_sector(uint32_t rw, void *ptr, uint32_t lba, uint8_t sectors);
void test_rw();

struct [[gnu::packed]] fs_node {
    char name[128];
    uint16_t size;
    uint16_t next;
    uint16_t nodes[190]; // 文件大小最大占用块数量
};

#define HEADER_NODES 100
#define BLOCK_SIZE 512

static struct fs_node *fs_header;

int str_cmp(char *a, char *b);
uint32_t str_len(char *str);

void ls_dir();
void *read_file(char *filename);
struct fs_node *search_file(char *filename);
void cat(char *file);
// void touch_file(char *filename, uint16_t file_size);
// void del_file(char *filename);

void test_fs_read_ls();

#endif
