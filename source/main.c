/* main.c for XinOS */

#include "xinos.h"

int main(void) {
    string str = "strlen(\"system\") = ";

    clear();
    mvaddstr("Welcome!", 10, 30, 0x0C);
    mvaddstr("This is the XinOS...", 12, 30, 0x09);
    mvaddstr(str, 14, 30, 0x0A);
    mvaddch(strlen("system") + '0', 14, 49, 0);
    return 0;
}
