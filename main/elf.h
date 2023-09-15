#ifndef _ELF_h_
#define _ELF_h_

#include <stdint.h>

#define Elf32_Word uint32_t
#define Elf32_Off uint32_t
#define Elf32_Addr uint32_t
#define Elf32_Half uint32_t

/*
 * todo: 加载elf执行文件的过程：
 *      1. 判断文件头magic，确定文件是不是elf文件；
 *      2. 从elf header中得到程序头的位置、条目大小、条目数量；
 *      3. 建立逻辑内存与物理内存的映射关系。
 *              这里需要为每个进程建立一个内存映射目录。
 *      4. 将所有段从文件中加载到逻辑内存中，会自动映射进对应的物理内存。
 */

// ELF header
#define EI_NIDENT 16
typedef struct {
    unsigned char e_ident[EI_NIDENT];
    Elf32_Half e_type;
    Elf32_Half e_machine;
    Elf32_Word e_version;
    Elf32_Addr e_entry;         // 执行位置
    Elf32_Off e_phoff;          // 程序头在文件中的偏移
    Elf32_Off e_shoff;          // 节区头在文件中的偏移
    Elf32_Word e_flags;
    Elf32_Half e_ehsize;        // elf标头大小
    Elf32_Half e_phentsize;     // 程序头每个条目的大小，每个条目大小一致
    Elf32_Half e_phnum;         // 程序头的条目数
    Elf32_Half e_shentsize;     // 节区头每个条目的大小，每个条目大小一致
    Elf32_Half e_shnum;         // 节区头条目数
    Elf32_Half e_shstrndx;
} Elf32_Ehdr;

// ELF Program Header, is array in memory layout
typedef struct {
    Elf32_Word p_type;
    Elf32_Off p_offset;
    Elf32_Addr p_vaddr;  // 段在文件中的位置
    Elf32_Addr p_paddr;  // 段在内存中的位置
    Elf32_Word p_filesz; // 段在文件中的大小
    Elf32_Word p_memsz;  // 段在内存中的大小
    Elf32_Word p_flags;
    Elf32_Word p_align;
} Elf32_Phdr;

// Section Header
typedef struct {
    Elf32_Word sh_name;
    Elf32_Word sh_type;
    Elf32_Word sh_flags;
    Elf32_Addr sh_addr;
    Elf32_Off sh_offset;
    Elf32_Word sh_size;
    Elf32_Word sh_link;
    Elf32_Word sh_info;
    Elf32_Word sh_addralign;
    Elf32_Word sh_entsize;
} Elf32_Shdr;

#endif