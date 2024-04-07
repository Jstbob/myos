#include <stdint.h>

/* struct multiboot_tag_basic_meminfo *tag_mem
    = (struct multiboot_tag_basic_meminfo *)get_mbi(
        mbi_l, MULTIBOOT_TAG_TYPE_BASIC_MEMINFO); */
// from grub2 get mbi by type
uint32_t *get_mbi(uint32_t *mbi_l, uint32_t des_type) {
    uint32_t *ptr_tag = mbi_l + 2;
    uint32_t type;
    while ((type = *(ptr_tag)) != 0) {
        if (type == des_type) {
            return ptr_tag;
        }
        ptr_tag += *(ptr_tag + 1);
    }
    return 0;
}

void kernel_main(uint32_t *mbi_l) {
}
