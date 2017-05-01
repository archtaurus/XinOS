/* screen.c for XinOS */

#include "types.h"
#include "string.h"
#include "screen.h"

// Bit 76543210
//     ||||||||
//     |||||^^^-fore colour
//     ||||^----fore colour bright bit
//     |^^^-----back colour
//     ^--------back colour bright bit OR enables blinking Text
typedef enum {
    COLOR_BLACK         = 0x00,
    COLOR_BLUE          = 0x01,
    COLOR_GREEN         = 0x02,
    COLOR_CYAN          = 0x03,
    COLOR_RED           = 0x04,
    COLOR_MAGENTA       = 0x05,
    COLOR_BROWN         = 0x06,
    COLOR_LIGHT_GRAY    = 0x07,
    COLOR_DARK_GRAY     = 0x08,
    COLOR_LIGHT_BLUE    = 0x09,
    COLOR_LIGHT_GREEN   = 0x0A,
    COLOR_LIGHT_CYAN    = 0x0B,
    COLOR_LIGHT_RED     = 0x0C,
    COLOR_LIGHT_MAGENTA = 0x0D,
    COLOR_YELLOW        = 0x0E,
    COLOR_WHITE         = 0x0F,
} color_t;

// http://wiki.osdev.org/Bare_Bones#Writing_a_kernel_in_C
//
static inline uint8_t entry_color(color_t fgcolor, color_t bgcolor) {
    return fgcolor | bgcolor << 4;
}

static inline uint16_t entry(uint8_t ch, uint8_t color) {
    return (uint16_t) ch | (uint16_t) color << 8;
}

uint16_t screenW = 80;     // 屏幕宽
uint16_t screenH = 25;     // 屏幕高
uint16_t cursorX = 0;      // 光标X
uint16_t cursorY = 0;      // 光标Y
bool     hidden  = false;  // 光标隐藏
uint8_t  fgcolor = COLOR_WHITE;  // 当前前景颜色
uint8_t  bgcolor = COLOR_BLACK;  // 当前背景颜色
uint8_t  color   = COLOR_WHITE;  // 当前颜色
uint8_t  padding = ' ';    // 当前填充字符

// 内存地址B8000段开始的4000字节用于储存文本模式下的屏幕内容
volatile uint8_t *screen  = (volatile uint8_t *)0xB8000;

/* 清空屏幕 */
void cls(void) {
    uint16_t pad = color << 8 | padding;
    volatile uint16_t *p = (volatile uint16_t *)screen;
    while(p < (volatile uint16_t *)(screen + screenW * screenH * 2))
        *p++ = pad;
}

/* 返回指定位置上字符的序号 */
uint16_t getchidx(uint16_t row, uint16_t col) {
    return (80 * row + col) * 2;
}

/* 指定位置和颜色输出字符 */
void putcat(char ch, uint16_t row, uint16_t col, uint8_t color) {
    uint16_t i = getchidx(row, col);
    screen[i] = ch;
    if(color) screen[i+1] = color;
}

/* 指定位置和颜色输出字符串 */
void putsat(const char *str, uint16_t row, uint16_t col, uint8_t color) {
    volatile uint8_t *p = (volatile uint8_t *)screen + getchidx(row, col);
    while(*str != 0) {
        *p++ = *str++;
        if(color) *p = color;
        p++;
    }
}
