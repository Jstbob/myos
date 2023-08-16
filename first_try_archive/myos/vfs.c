#include "vfs.h"
#include "common.h"
#include "monitor.h"
#include <stdint.h>

struct fs_header *root_header;
struct file_block *raw;

void init_root_node(uint32_t mount_point_addr) {
    root_header = (struct fs_header *)mount_point_addr;
    raw = (struct file_block *)(mount_point_addr + 512 * 1024);
}

void ls() {
    for (uint16_t i = 0; i < root_header->file_number; ++i) {
        monitor_print_msg(root_header->nodes[i].filename, 128);
        enter_new_line();
    }
}

void print_first_filename() {
    monitor_print_msg(root_header->nodes[0].filename, 128);
}