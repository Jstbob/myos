#include "process.h"
#include "asm.h"
#include "boot.h"
#include "console.h"
#include "elf.h"
#include "fs.h"
#include "idt.h"
#include "mem_r.h"

extern kernel_pt[KERNEL_PAGE_ENTRIES];
extern kernel_pd[PD_COUNT];

// 有多少可以使用的内存页
void init_available_mem(uint32_t mem_cap) {
    // TODO: 需要修改
    mem_cap = 128 * 1024 * 1024;
    if (mem_cap <= KERNEL_MEMORY) {
        print_msg("memory cap: ");
        print_uint32(mem_cap);
        print_msg(", ");
        panic("mem cap is not enough!");
    }

    available_pages = mem_cap / PAGE_SIZE;
    next_page_index = KERNEL_MEMORY / PAGE_SIZE;
}

uint32_t alloc_pages(uint32_t pages) {
    uint32_t tmp = next_page_index + pages;
    if (tmp >= alloc_pages) {
        panic("mem cap is not enough, alloc pages fail.");
    }

    uint32_t ret_index = next_page_index;
    next_page_index = tmp;
    return ret_index;
}

static uint32_t alloced_pages = 0;
void free_pages(uint32_t count) {
    next_page_index -= count;
    alloced_pages = 0;
}

// TODO
static void *file_first_block = 0;
main_t load_elf(char *name) {
    struct fs_node *node = search_file(name);
    if (!node) {
        print_msg("file is not exist.\n");
        return 0;
    }

    file_first_block = krmalloc(BLOCK_SIZE);
    ata_read_one_sector(file_first_block, node->nodes[0]);
    Elf32_Ehdr *elf_header = (Elf32_Ehdr *)file_first_block;
    Elf32_Phdr *elf_program_header
        = (Elf32_Phdr *)(file_first_block + sizeof(Elf32_Ehdr));

    // 将物理地址映射到逻辑地址
    for (int i = 0; i <= elf_header->e_phnum; ++i) {
    }
}

void create_process() {
    close_keyboard();
    char name[128];
    int args;
    char **argv;
    if (parse_option(&name, &args, &argv) != 0) {
        print_msg("parse option is fail.\n");
        goto exit;
    }

    main_t main_entry = load_elf(name);

    // 读取文件到内存
    if (main_entry == 0) {
        print_msg("load elf is fail.\n");
        goto exit;
    }

    int ret_v = main_entry(args, argv);
    if (ret_v != 0) {
        print_msg("run is error, return code: ");
        print_uint32(ret_v);
        print_msg("\n");
        goto exit;
    }

exit:
    krfree(file_first_block);
    free_pages(alloced_pages);
    keyboard_flush();
    open_keyboard();
}

void first_process() {
    while (1) {
        print_msg("/#");
        while (start_process_flag == 0) {
        }
        create_process();
    }
}
