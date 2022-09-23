#include <exqos/tty/tty.h>
#include <stdint.h>

// [0xB8000, 0xBFFFF]
vga_attributes *tty_buffer = 0xB8000;
vga_attributes theme_color = VGA_COLOR_BLACK;

// 控制下一个字符输出位置
uint32_t TTY_COL = 0;
uint16_t TTY_ROW = 0;

// 设置屏幕的前景色和后景色
void tty_set_theme(vga_attributes fg, vga_attributes bg) {
    theme_color = (bg << 4 | fg) << 8;
}

// 打印单个字符
void tty_put_char(char chr) {
    
    vga_attributes attr = theme_color | chr;
    // 将字符和颜色信息载入显存缓存
    *(tty_buffer + TTY_COL + TTY_ROW * TTY_WIDTH) = attr; 

    TTY_COL ++;
    // 检查是否需要换行
    if (TTY_COL >= TTY_WIDTH) {
        TTY_COL = 0;
        TTY_ROW ++;
        // 当屏幕无法显示全部字符，则窗口上滚一行
        if (TTY_ROW >= TTY_HEIGHT) {
            tty_scroll_up();
            TTY_ROW --;
        }
    }

}

// 打印字符串
void tty_put_str(char* str) {
    while (*str != '\0') {
        tty_put_char(*str);
        str ++;
    }
}

// 屏幕上滚
void tty_scroll_up() {
    // use memcpy
}

// 清空屏幕
void tty_clear() {
    for (uint32_t x = 0 ; x < TTY_WIDTH ; x ++ ) {
        for (uint32_t y = 0 ; y < TTY_HEIGHT ; y ++ ) {
            * (tty_buffer + y * TTY_WIDTH + x) = ' ';
        }
    }
}