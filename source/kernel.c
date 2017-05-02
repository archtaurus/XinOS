/* kernel.c for XinOS */

#include "xinos.h"

int kmain(void) {
	char *str = "strlen(\"system\") = ";

	terminal_init();
	terminal_puts("Welcome!", 10, 30, 0x0C);
	terminal_puts("This is the XinOS...", 12, 30, 0x09);
	terminal_puts(str, 14, 30, 0x0A);
    terminal_move(14, 49);
    terminal_putc(strlen("system") + '0');

	return 0;
}
