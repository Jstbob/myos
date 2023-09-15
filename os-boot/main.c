#include <stdint.h>
#include <stdio.h>

extern int _bin_end;
extern int __data_start;
extern int _end;
extern int _init;

int main() {
    printf("%p\n", _bin_end - _init + 0x1000);     // 0x31800 // 0x1000
    printf("%p\n", __data_start - _init + 0x1000); // 0x31800 // 0x1000
    printf("%p\n", _end - _init + 0x1000);         // 0x31800 // 0x1000
    return 0;
}
