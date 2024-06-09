#include "fs.h"
#include "asm.h"
#include "console.h"
#include "mem_r.h"

/*
;  Technical Information on the ports:
;      Port    Read/Write   Misc
;     ------  ------------ -------------------------------------------------
;       1f0       r/w       data register, the bytes are written/read here
;       1f1       r         error register  (look these values up yourself)
;       1f2       r/w       sector count, how many sectors to read/write
;       1f3       r/w       sector number, the actual sector wanted
;       1f4       r/w       cylinder low, cylinders is 0-1024
;       1f5       r/w       cylinder high, this makes up the rest of the 1024
;       1f6       r/w       drive/head
;                              bit 7 = 1
;                              bit 6 = 0
;                              bit 5 = 1
;                              bit 4 = 0  drive 0 select
;                                    = 1  drive 1 select
;                              bit 3-0    head select bits
;       1f7       r         status register
;                              bit 7 = 1  controller is executing a command
;                              bit 6 = 1  drive is ready
;                              bit 5 = 1  write fault
;                              bit 4 = 1  seek complete
;                              bit 3 = 1  sector buffer requires servicing
;                              bit 2 = 1  disk data read corrected
;                              bit 1 = 1  index - set to 1 each revolution
;                              bit 0 = 1  previous command ended in an error
;       1f7       w         command register
;                            commands:
;                              50h format track
;                              20h read sectors with retry
;                              21h read sectors without retry
;                              22h read long with retry
;                              23h read long without retry
;                              30h write sectors with retry
;                              31h write sectors without retry
;                              32h write long with retry
;                              33h write long without retry
*/

#define IDE_BSY 0x80
#define IDE_DRDY 0x40
#define IDE_DRDY 0x40
#define IDE_DF 0x20
#define IDE_ERR 0x01

int idewait(int checkerr) {
    int r;

    while (((r = inb(0x1f7)) & (IDE_BSY | IDE_DRDY)) != IDE_DRDY)
        ;
    if (checkerr && (r & (IDE_DF | IDE_ERR)) != 0)
        return -1;
    return 0;
}

void init_fs() {
    // 选择硬盘0, LBA寻址模式
    outb(0x1f6, 0xe0);

    for (int i = 0; i < 1000; i++) {
        uint8_t r;
        if ((r = inb(0x1f7)) == 0 && i == 999) {
            panic("disk 0x1f7 port found error");
        }
    }

    // 获取硬盘格式的头部
    fs_header
        = (struct fs_node *)krmalloc(sizeof(struct fs_node) * HEADER_NODES);
    struct fs_node *cur = fs_header;
    for (int i = 0; i < HEADER_NODES; ++i) {
        ata_read_one_sector((uint32_t)cur, i);
        ++cur;
    }

    // // BUG
    // rw_sector(MODE_READ, (void *)fs_header, 0, HEADER_NODES);
}

// TODO: 通过1f7来判断状态
// LBA读取数据到缓冲区，lba
void rw_sector(uint32_t rw, void *ptr, uint32_t lba, uint8_t sectors) {
    idewait(0);
    outb(0x1f2, sectors); // 扇区的数量, 不能超过256
    outb(0x1f3, lba & 0xff);
    outb(0x1f4, (lba >> 8) & 0xff);
    outb(0x1f5, (lba >> 16) & 0xff);
    if (rw == MODE_READ) {
        outb(0x1f7, 0x20);
        if (idewait(1))
            panic("ide read error");
        _read_sector((uint32_t)ptr, sectors);
    } else {
        outb(0x1f7, 0x30);
        if (idewait(1))
            panic("ide read error");
        _write_sector((uint32_t)ptr, sectors);
    }
}

// 测试读写扇区, 2023/9/28测试通过
void test_rw() {
    void *ptr = krmalloc(BLOCK_SIZE);

    // 读取0号扇区
    rw_sector(MODE_READ, ptr, 0, 1);
}

// 第一个扇区保留
void ls_dir() {
    print_msg("filename            size\n"); // 25宽度对齐
    for (struct fs_node *cur = &fs_header[1]; cur->next;
         cur = &fs_header[cur->next]) {
        print_msg(cur->name);
        for (int i = 0; i < 25 - 4 - str_len(cur->name); ++i) {
            print_msg(" ");
        }
        print_uint32(cur->size);
        print_msg("\n");
    }
}

// 得到链表上最后一个节点，方便增加文件
struct fs_node *get_end_node() {
    struct fs_node *cur = &fs_header[1];
    for (; cur->next; cur = &fs_header[cur->next]) {
    }
    return cur;
}

// 搜索链表上的文件
struct fs_node *search_file(char *filename) {
    for (struct fs_node *cur = &fs_header[1]; cur->next;
         cur = &fs_header[cur->next]) {
        if (str_cmp(cur->name, filename)) {
            return cur;
        }
    }
    return 0;
}

int str_cmp(char *a, char *b) {
    for (int i = 0; a[i] == b[i]; ++i) {
        if (a[i] == '\0') {
            return 1;
        }
    }
    return 0;
}

uint32_t str_len(char *str) {
    uint32_t len = 0;
    while ((*str) != '\0') {
        ++len;
        ++str;
    }
    return len;
}

void *read_file(char *filename) {
    struct fs_node *node = search_file(filename);
    if (!node)
        return 0;

    // 得到文件需要占用多少个块
    uint16_t count = (node->size + BLOCK_SIZE) / BLOCK_SIZE;
    void *ptr = krmalloc(BLOCK_SIZE * count);
    void *cur = ptr;

    for (int i = 0; i < 190; ++i) {
        uint16_t tmp = node->nodes[i];
        if (!tmp)
            break;
        ata_read_one_sector((uint32_t)cur, tmp);
        cur += BLOCK_SIZE;
    }
    return ptr;
}

// 每次读取文件后，需要关闭文件
void close_file(void *file) {
    if (file)
        krfree(file);
}

// 寻找第一个空节点
struct fs_node *search_first_null_node() {
    for (uint16_t i = 1; i < HEADER_NODES; ++i) {
        struct fs_node *cur = &fs_header[i];
        if (cur->size == 0) {
            return cur;
        }
    }
}

// // 创建文件
// void touch_file(char *filename, uint16_t file_size) {
//     struct fs_node *tmp = search_first_null_node();
//     mem_cpy(filename, tmp->name, str_len(filename));
//     tmp->size = file_size;
//     tmp->next = 0;
//     // 怎么判断哪些块被占用了？
//     struct fs_node *end = get_end_node();
// }

// 测试成功，2023/9/19
void test_fs_read_ls() {
    ls_dir();
    void *ptr = read_file("helloworld.txt");
    print_msg((char *)ptr);
    close_file(ptr);
}

void cat(char *file) {
    void *ptr = read_file(file);
    if (ptr == 0) {
        print_msg("file is not exist.\n");
        return;
    }
    print_msg((char *)ptr);
    close_file(ptr);
}
