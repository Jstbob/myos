#include "fs.h"
#include <cstring>
#include <fcntl.h>
#include <filesystem>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

namespace fs = std::filesystem;

uint16_t cur_header_index = 1;
uint16_t cur_data_node = HEADER_NODES;

void get_files(std::vector<std::string> &files) {
    for (auto &p : fs::directory_iterator("./bin")) {
        std::string file_name = p.path().string();
        // std::cout << file_name << std::endl;
        files.push_back(file_name);
    }
}

std::string get_filename(std::string path) {
    fs::path file_path(path);
    return file_path.filename().string();
}

void add_bin(std::string file) {
    int fd = open("fs.img", O_RDWR);
    if (fd == -1) {
        std::cerr << "Error opening file" << std::endl;
        exit(EXIT_FAILURE);
    }

    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1) {
        std::cerr << "Error getting file size" << std::endl;
        close(fd);
        exit(EXIT_FAILURE);
    }

    void *mapped_memory
        = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_memory == MAP_FAILED) {
        std::cerr << "Error mapping file to memory" << std::endl;
        close(fd);
        exit(1);
    }

    char *data = static_cast<char *>(mapped_memory);

    // do somethine
    FILE *f = fopen(file.c_str(), "r");
    off_t f_size = fs::file_size(file);
    std::cout << file << std::endl;
    std::cout << f_size << std::endl;
    uint16_t blocks = (f_size + 512) / 512;
    fs_header = (struct fs_node *)mapped_memory;
    std::string name = get_filename(file);
    struct fs_node *node = &fs_header[cur_header_index];

    std::strcpy(node->name, name.c_str());
    node->size = f_size;
    node->next = cur_header_index + 1;
    std::cout << blocks << std::endl;
    for (int i = 0; i < blocks; ++i) {
        node->nodes[i] = cur_data_node;
        ++cur_data_node;
    }

    void *des_ptr = (void *)&fs_header[node->nodes[0]];
    fread(des_ptr, 1, f_size, f);
    fclose(f);

    ++cur_header_index;

    if (msync(mapped_memory, file_size, MS_SYNC) == 0) {
        std::cout << "msync is sucess." << std::endl;
    } else {
        std::cerr << "Error syncing memory to file" << std::endl;
    }
    munmap(mapped_memory, file_size);
    close(fd);
}

// 添加.elf到硬盘中
int main() {
    std::vector<std::string> files;
    get_files(files);

    for (auto &file : files) {
        add_bin(file);
    }

    // std::cout<<sizeof(fs_node)<<std::endl;
}
