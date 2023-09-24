#include <stdio.h>

int main() {
    // printf("%c\n", '\x00');
    char *str = "he";
    if (str[2] == '\x00') {
        printf("y\n");
    } else {
        printf("n\n");
    }
}
