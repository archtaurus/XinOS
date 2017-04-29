/* screen.h for XinOS */

#ifndef SCREEN_H
#define SCREEN_H

void clear(void);
void mvaddstr(const string, uint8, uint8, int);
void mvaddch(const char, uint8, uint8, int);

#endif