/* screen.c for XinOS */

int color = 0x07;
volatile char *screen = (volatile char*)0xB8000;

/* 清空屏幕 */
void clear(void) {
    unsigned int i = 0;
    while(i < 4000) {
        screen[i++] = ' ';
        screen[i++] = color;
    }
}

/* 在指定位置输出字符串 */
void mvaddstr(const char* str, int row, int col, int color) {
    int i = 0;
    int j = (80 * row + col) * 2;
    while(str[i]) {
        screen[j] = str[i];
        if(color) screen[j + 1] = color;
        i ++;
        j += 2;
    }
}