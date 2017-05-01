/* terminal.h for XinOS */

#ifndef SCREEN_H
#define SCREEN_H

typedef enum {
    COLOR_BLACK         = 0x00,
    COLOR_BLUE          = 0x01,
    COLOR_GREEN         = 0x02,
    COLOR_CYAN          = 0x03,
    COLOR_RED           = 0x04,
    COLOR_MAGENTA       = 0x05,
    COLOR_BROWN         = 0x06,
    COLOR_LIGHT_GRAY    = 0x07,
    COLOR_DARK_GRAY     = 0x08,
    COLOR_LIGHT_BLUE    = 0x09,
    COLOR_LIGHT_GREEN   = 0x0A,
    COLOR_LIGHT_CYAN    = 0x0B,
    COLOR_LIGHT_RED     = 0x0C,
    COLOR_LIGHT_MAGENTA = 0x0D,
    COLOR_YELLOW        = 0x0E,
    COLOR_WHITE         = 0x0F,
} color_t;

// http://wiki.osdev.org/Bare_Bones#Writing_a_kernel_in_C
//
// static inline uint8_t entry_color(color_t fgcolor, color_t bgcolor){
//     return  bgcolor << 4 | fgcolor;
// }
//
// static inline uint16_t entry(uint8_t ch, uint8_t entry_color) {
//     return (uint16_t) ch | (uint16_t) entry_color << 8;
// }

void cls(void);
size_t getchidx(size_t, size_t) ;
void putcat(char, size_t, size_t, uint8_t);
void putsat(const char *, size_t, size_t, uint8_t);

#endif