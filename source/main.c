/* main.c for XinOS */

#include "xinos.h"

int main(void) {
    string str = "strlen(\"system\") = ";

    cls();
    putsat("Welcome!", 10, 30, 0x0C);
    putsat("This is the XinOS...", 12, 30, 0x09);
    putsat(str, 14, 30, 0x0A);
    putcat(strlen("system") + '0', 14, 49, NULL);
    return 0;
}
