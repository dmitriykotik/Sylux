#include "../drivers/vga.h"

void kernel_main(void) {
    vga_write("Hello, World!");
}
