/* kernel.c for XinOS */

#include "xinos.h"

int kmain(void) {
	char *str = "strlen(\"system\") = ";

	initscr();
	putsat("Welcome!", 10, 30, 0x0C);
	putsat("This is the XinOS...", 12, 30, 0x09);
	putsat(str, 14, 30, 0x0A);
	putcat(strlen("system") + '0', 14, 49, 0);

	return 0;
}
