/* screen.c for XinOS */

#include "types.h"
#include "string.h"
#include "screen.h"

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
size_t getchidx(size_t row, size_t col) {
    return (80 * row + col) * 2;
}

/* 指定位置和颜色输出字符 */
void putcat(char ch, size_t row, size_t col, uint8_t color) {
    size_t i = getchidx(row, col);
    screen[i] = ch;
    if(color) screen[i+1] = color;
}

/* 指定位置和颜色输出字符串 */
void putsat(const char *str, size_t row, size_t col, uint8_t color) {
    volatile uint8_t *p = (volatile uint8_t *)screen + getchidx(row, col);
    while(*str != 0) {
        *p++ = *str++;
        if(color) *p = color;
        p++;
    }
}
