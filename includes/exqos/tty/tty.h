#include <exqos/tty/vga.h>

typedef unsigned short vga_attributes;

#define TTY_WIDTH 80
#define TTY_HEIGHT 25

// 设置屏幕的前景色和后景色
void tty_set_theme(vga_attributes fg, vga_attributes bg);

// 打印单个字符
void tty_put_char(char chr);

// 打印字符串
void tty_put_str(char* str);

// 屏幕上滚
void tty_scroll_up();

// 清空屏幕
void tty_clear();