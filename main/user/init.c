#include <stdint.h>

int main() {
    while (1) {
        print("/#");
        char file[128];
        wait_input(&file);
        uint32_t ret_v = exec(file);
        if(ret_v != 0){
            print("run is fail.");
        }
    }
}
