/* kernel.c : actual kernel */

#include <exqos/tty/tty.h>
#include <exqos/arch/gdt.h>

void _kernel_init(void) {
    _init_gdt();
    tty_set_theme(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

void _kernel_main(void* info_table) {
    tty_put_str("Hello, Kernel World from LUT!");
}