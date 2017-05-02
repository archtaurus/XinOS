/* terminal.c for XinOS */

#include "types.h"
#include "string.h"
#include "terminal.h"

static const uint8_t terminal_width  = 80;
static const uint8_t terminal_height = 25;
// 内存地址B8000段开始的4000字节用于储存文本模式下的屏幕内容
static const uint16_t *terminal_buffer_top = (uint16_t *)0xB8000;
static const uint16_t *terminal_buffer_end = (uint16_t *)0xB8000 + 4000;

uint8_t terminal_cursor_row;
uint8_t terminal_cursor_column;
color_t terminal_background_color;
color_t terminal_foreground_color;
color_t terminal_color;
volatile uint16_t *terminal_ptr;

/* 返回指定位置上字符的序号 */
static inline uint16_t terminal_entry_index(uint8_t row, uint8_t col) {
    return 80 * row + col;
}

static inline color_t terminal_entry_color(color_t bgcolor, color_t fgcolor){
    return  bgcolor << 4 | fgcolor;
}

static inline uint16_t terminal_entry(uint8_t ch, color_t color) {
    return (uint16_t) ch | (uint16_t) color << 8;
}

/* 初始化终端窗口 */
void terminal_init(void) {
    terminal_set_color(COLOR_BLACK, COLOR_WHITE);
    terminal_clear();
}

void terminal_set_fgcolor(color_t fgcolor) {
    terminal_foreground_color = fgcolor;
    terminal_color = terminal_entry_color(terminal_background_color,
                                          terminal_foreground_color);
}

void terminal_set_bgcolor(color_t bgcolor) {
    terminal_background_color = bgcolor;
    terminal_color = terminal_entry_color(terminal_background_color,
                                          terminal_foreground_color);
}

void terminal_set_color(color_t bgcolor, color_t fgcolor) {
    terminal_foreground_color = bgcolor;
    terminal_foreground_color = fgcolor;
    terminal_color = terminal_entry_color(terminal_background_color,
                                          terminal_foreground_color);
}

/* 清空屏幕 */
void terminal_clear(void) {
    terminal_ptr = (volatile uint16_t *)terminal_buffer_top;
    const uint16_t e = terminal_entry(' ', terminal_color);
    while(terminal_ptr < terminal_buffer_end) *(terminal_ptr++) = e;
    terminal_move(0, 0);
}

void terminal_move(uint8_t row, uint8_t col) {
    terminal_cursor_row    = row;
    terminal_cursor_column = col;
    terminal_ptr = (volatile uint16_t *)terminal_buffer_top + terminal_entry_index(row, col);
}

/* 输出字符 */
void terminal_putc(char ch) {
    *((uint8_t *)terminal_ptr++) = ch;
}

/* 指定位置和颜色输出字符串 */
void terminal_puts(const char *str, uint8_t row, uint8_t col, color_t color) {
    volatile uint8_t *p = (volatile uint8_t *)terminal_buffer_top + terminal_entry_index(row, col)*2;
    while(*str != 0) {
        *p++ = *str++;
        if(color) *p = color;
        p++;
    }
}
