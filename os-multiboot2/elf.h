#include <stdint.h>

#define EI_NIDENT 16
#define Elf32_Addr uint32_t
#define Elf32_Half uint16_t
#define Elf32_Off uint32_t
#define Elf32_Sword uint32_t
#define Elf32_Word uint32_t

// elf header, 54 Bytes
typedef struct {
    unsigned char e_ident[EI_NIDENT];   //  2
    Elf32_Half e_type;      // 4
    Elf32_Half e_machine;   // 4
    Elf32_Word e_version;   // 4
    Elf32_Addr e_entry;     // 4
    Elf32_Off e_phoff;      // 4
    Elf32_Off e_shoff;      // 4
    Elf32_Word e_flags;     // 4
    Elf32_Half e_ehsize;    // 4
    Elf32_Half e_phentsize;     // 4
    Elf32_Half e_phnum;         // 4
    Elf32_Half e_shentsize;     // 4
    Elf32_Half e_shnum;         // 4
    Elf32_Half e_shstrndx;      // 4
} __attribute__((packed)) Elf32_Ehdr;

// Program header, 32 Bytes
typedef struct {
    Elf32_Word p_type;      // 4
    Elf32_Off p_offset;     // 4
    Elf32_Addr p_vaddr;     // 4
    Elf32_Addr p_paddr;     // 4
    Elf32_Word p_filesz;    // 4
    Elf32_Word p_memsz;     // 4
    Elf32_Word p_flags;     // 4
    Elf32_Word p_align;     // 4
} Elf32_Phdr;

// ... section data

// Section header, 40 Bytes
typedef struct {
    Elf32_Word sh_name;
    Elf32_Word sh_type;
    Elf32_Word sh_flags;
    Elf32_Addr sh_addr;  // Virtual address of the section in memory.
    Elf32_Off sh_offset; // Offset of the section in the file image.
    Elf32_Word sh_size;  
    Elf32_Word sh_link;
    Elf32_Word sh_info;
    Elf32_Word sh_addralign;
    Elf32_Word sh_entsize;
} __attribute__((packed)) Elf32_Shdr;

void load_elf(uint8_t* pa); //  load elf to point memory address