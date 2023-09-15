#include <stdio.h>

extern unsigned int add(unsigned int, unsigned int);

int main() {
    unsigned int sum = add(1, 2);
    printf("%d\n", sum);
}
