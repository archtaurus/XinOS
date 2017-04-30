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
#define BLACK 			0x00
#define BLUE 			0x01
#define GREEN 			0x02
#define CYAN 			0x03
#define RED 			0x04
#define MAGENTA 		0x05
#define BROWN 			0x06
#define LIGHT_GRAY 		0x07
#define DARK_GRAY 		0x08
#define LIGHT_BLUE 		0x09
#define LIGHT_GREEN 	0x0A
#define LIGHT_CYAN 		0x0B
#define LIGHT_RED 		0x0C
#define LIGHT_MAGENTA 	0x0D
#define YELLOW 			0x0E
#define WHITE 			0x0F

// int screen_width = 80;
// int screen_height = 25;
// int total_characters = screen_width * screen_height;
// int screen_data_size = total_characters * 2;
uint16	cursorX	= 0;
uint16	cursorY	= 0;
uint8	fgcolor	= WHITE;	// 当前的前景颜色
uint8	bgcolor	= BLACK;	// 当前的背景颜色
uint8	color	= 0x0F;		// bgcolor << 4 | fgcolor;
uint8	padding	= ' ';		// 当前的填充字符
volatile char *screen = (volatile char *)0xB8000;

/* 清空屏幕 */
void cls(void) {
	uint16 i = 0;
	uint16 ch = padding | (color << 8);
	volatile uint16 *screen = (volatile uint16 *)0xB8000;
	while(i < 2000) screen[i++] = ch;
}

/* 在指定位置输出字符串 */
void putsat(const char *str, uint16 row, uint16 col, uint8 color) {
	char ch;
	uint16 i = 0;
	uint16 j = (80 * row + col) * 2;
	while(ch = str[i++]) {
		screen[j++] = ch;
		if(color) screen[j++] = color;
	}
}

/* 在指定位置输出字符 */
void putcat(char ch, uint16 row, uint16 col, uint8 color) {
	uint16 i = (80 * row + col) * 2;
	screen[i] = ch;
	if(color) screen[i + 1] = color;
}
