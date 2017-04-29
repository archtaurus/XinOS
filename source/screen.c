/* screen.c for XinOS */

#include "types.h"
#include "screen.h"

int cursorX = 0;
int cursorY = 0;
uint8 color   = 0x0F;
volatile char *screen = (volatile char*)0xB8000;

/* 清空屏幕 */
void cls(void) {
	int i = 0;
	while(i < 4000) {
		screen[i++] = ' ';
		screen[i++] = color;
	}
}

/* 在指定位置输出字符串 */
void putsat(const char *str, int row, int col, uint8 color) {
	int i = 0;
	int j = (80 * row + col) * 2;
	while(str[i]) {
		screen[j] = str[i];
		if(color) screen[j + 1] = color;
		i ++;
		j += 2;
	}
}

/* 在指定位置输出字符 */
void putcat(char ch, int row, int col, uint8 color){
	int i = (80 * row + col) * 2;
	screen[i] = ch;
	if(color) screen[i + 1] = color;
}