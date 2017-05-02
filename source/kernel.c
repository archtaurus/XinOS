/* kernel.c for XinOS */

#include "xinos.h"

int kmain(void) {
	char *str = "strlen(\"system\") = ";

	terminal_init();
	terminal_move_to(10, 30);
	terminal_set_fgcolor(COLOR_LIGHT_RED);
	terminal_puts("Welcome!");
	terminal_move_to(12, 30);
	terminal_set_fgcolor(COLOR_LIGHT_BLUE);
	terminal_puts("This is the XinOS...");
	terminal_move_to(14, 30);
	terminal_set_fgcolor(COLOR_LIGHT_GREEN);
	terminal_puts(str);
	terminal_move_to(14, 49);
	terminal_set_fgcolor(COLOR_WHITE);
	terminal_putc(strlen("system") + '0');
	for(int i=0; i<100; ++i){
		terminal_puts("Hello, world! ");
	}

	return 0;
}
