/* terminal.c for XinOS */

#include "types.h"
#include "string.h"
#include "terminal.h"

static const uint8_t TERMINAL_WIDTH  = 80;
static const uint8_t TERMINAL_HEIGHT = 25;
// 内存地址B8000段开始的4000字节用于储存文本模式下的屏幕内容
static const uint16_t *TERMINAL_BUFFER_TOP = (uint16_t *)0xB8000;
static const uint16_t *TERMINAL_BUFFER_END = (uint16_t *)0xB8000 + 4000;

volatile uint16_t *terminal_buffer_ptr;
uint8_t terminal_cursor_row;
uint8_t terminal_cursor_column;
color_t terminal_background_color;
color_t terminal_foreground_color;
color_t terminal_color;

static inline uint16_t terminal_entry_index(uint8_t row, uint8_t col) {
	return TERMINAL_WIDTH * row + col;
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
	terminal_buffer_ptr = (volatile uint16_t *)TERMINAL_BUFFER_TOP;
	const uint16_t e = terminal_entry(' ', terminal_color);
	while(terminal_buffer_ptr < TERMINAL_BUFFER_END) *(terminal_buffer_ptr++) = e;
	terminal_move_to(0, 0);
}

void terminal_move_to(uint8_t row, uint8_t col) {
	terminal_cursor_row    = row;
	terminal_cursor_column = col;
	terminal_buffer_ptr = (volatile uint16_t *)TERMINAL_BUFFER_TOP + terminal_entry_index(row, col);
}

/* 输出字符 */
void terminal_putc(char ch) {
	terminal_buffer_ptr++;
	if (++terminal_cursor_column == TERMINAL_WIDTH) {
		terminal_cursor_column = 0;
		if (++terminal_cursor_row == TERMINAL_HEIGHT) {
			terminal_scroll_up();
			terminal_cursor_row--;
			terminal_buffer_ptr -= TERMINAL_WIDTH;
		}
	}
	*terminal_buffer_ptr = terminal_entry(ch, terminal_color);
}

/* 输出字符串 */
void terminal_puts(const char *str) {
	while(*str) terminal_putc(*str++);
}

void terminal_scroll_up(void) {
	volatile uint16_t *p = (volatile uint16_t *)TERMINAL_BUFFER_TOP;
	while(p < (uint16_t *)TERMINAL_BUFFER_END - TERMINAL_WIDTH - 1) {
		*p = *(p + TERMINAL_WIDTH);
		p++;
	}
}