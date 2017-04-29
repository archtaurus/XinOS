/* screen.c for XinOS */

#include "types.h"
#include "screen.h"

char color = 0x0F;
volatile char *screen = (volatile char*)0xB8000;

/* 清空屏幕 */
void clear(void) {
    uint16 i = 0;
    while(i < 4000) {
        screen[i++] = ' ';
        screen[i++] = color;
    }
}

/* 在指定位置输出字符串 */
void mvaddstr(const char* string, uint8 row, uint8 col, int color) {
    int i = 0;
    int j = (80 * row + col) * 2;
    while(string[i]) {
        screen[j] = string[i];
        if(color) screen[j + 1] = color;
        i ++;
        j += 2;
    }
}