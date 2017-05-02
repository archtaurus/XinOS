/* terminal.c for XinOS */

#include "types.h"
#include "string.h"
#include "terminal.h"

static const size_t terminal_width  = 80;
static const size_t terminal_height = 25;
// 内存地址B8000段开始的4000字节用于储存文本模式下的屏幕内容
static const uint16_t *terminal_buffer_top = (uint16_t *)0xB8000;
static const uint16_t *terminal_buffer_end = (uint16_t *)0xB8000 + 4000;

size_t  terminal_cursor_row;
size_t  terminal_cursor_column;
uint8_t terminal_padding_char;
color_t terminal_foreground_color;
color_t terminal_background_color;
color_t terminal_color;

/* 返回指定位置上字符的序号 */
static inline size_t terminal_entry_index(size_t row, size_t col) {
    return (80 * row + col) * 2;
}

static inline color_t terminal_entry_color(color_t fgcolor, color_t bgcolor){
    return  bgcolor << 4 | fgcolor;
}

static inline uint16_t terminal_entry(uint8_t ch, color_t color) {
    return (uint16_t) ch | (uint16_t) color << 8;
}

/* 初始化终端窗口 */
void initscr(void) {
    terminal_cursor_row         = 0;
    terminal_cursor_column      = 0;
    terminal_padding_char       = 0x20;
    terminal_foreground_color   = COLOR_WHITE;
    terminal_background_color   = COLOR_BLACK;
    terminal_color              = terminal_entry_color(terminal_foreground_color,
                                                       terminal_background_color);
    cls();
}

/* 清空屏幕 */
void cls(void) {
    uint16_t  e = terminal_entry(terminal_padding_char, terminal_color);
    uint16_t *p = (uint16_t *)terminal_buffer_top;
    while(p < terminal_buffer_end) *p++ = e;
}

/* 指定位置和颜色输出字符 */
void putcat(char ch, size_t row, size_t col, uint8_t color) {
    size_t i = terminal_entry_index(row, col);
    if(color) {
        ((uint16_t *)terminal_buffer_top)[i] = terminal_entry(ch, color);
    } else {
        ((uint8_t *)terminal_buffer_top)[i] = ch;
    }
}

/* 指定位置和颜色输出字符串 */
void putsat(const char *str, size_t row, size_t col, uint8_t color) {
    volatile uint8_t *p = (volatile uint8_t *)terminal_buffer_top + terminal_entry_index(row, col);
    while(*str != 0) {
        *p++ = *str++;
        if(color) *p = color;
        p++;
    }
}
