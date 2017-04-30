/* screen.h for XinOS */

#ifndef SCREEN_H
#define SCREEN_H

void cls(void);
uint16_t chidx(uint16_t, uint16_t);
void putcat(char, uint16_t, uint16_t, uint8_t);
void putsat(const char *, uint16_t, uint16_t, uint8_t);

#endif