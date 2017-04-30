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
#define BLACK           0x00
#define BLUE            0x01
#define GREEN           0x02
#define CYAN            0x03
#define RED             0x04
#define MAGENTA         0x05
#define BROWN           0x06
#define LIGHT_GRAY      0x07
#define DARK_GRAY       0x08
#define LIGHT_BLUE      0x09
#define LIGHT_GREEN     0x0A
#define LIGHT_CYAN      0x0B
#define LIGHT_RED       0x0C
#define LIGHT_MAGENTA   0x0D
#define YELLOW          0x0E
#define WHITE           0x0F

uint16_t screenW = 80;     // 屏幕宽
uint16_t screenH = 25;     // 屏幕高
uint16_t cursorX = 0;      // 光标X
uint16_t cursorY = 0;      // 光标Y
uint8_t  fgcolor = WHITE;  // 当前前景颜色
uint8_t  bgcolor = BLACK;  // 当前背景颜色
uint8_t  color   = WHITE;  // 当前颜色
uint8_t  padding = ' ';    // 当前填充字符
uint8_t *screen  = (uint8_t *)0xB8000;  // 内存地址B8000段开始的4000字节用于储存文本模式下的屏幕内容

/* 清空屏幕 */
void cls(void) {
    uint16_t i = 0;
    uint16_t ch = padding | (color << 8);
    uint16_t *p = screen;
    while(i < screenW * screenH) p[i++] = ch;
}

uint16_t chidx(uint16_t row, uint16_t col) {
    return (80 * row + col) * 2;
}

/* 指定位置和颜色输出字符 */
void putcat(char ch, uint16_t row, uint16_t col, uint8_t color) {
    uint16_t i = chidx(row, col);
    screen[i] = ch;
    if(color) screen[i + 1] = color;
}

/* 指定位置和颜色输出字符串 */
void putsat(const char *str, uint16_t row, uint16_t col, uint8_t color) {
    char ch;
    uint16_t i = 0;
    uint16_t j = chidx(row, col);
    while(ch = str[i++]) {
        screen[j++] = ch;
        if(color) screen[j++] = color;
    }
}
