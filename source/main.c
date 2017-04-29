/* main.c for XinOS */

#include "screen.h"

int main(void) {
    clear();
    mvaddstr("Welcome!", 11, 30, 0);
    mvaddstr("This is the XinOS...", 13, 30, 0);
    return 0;
}
