#ifndef VGA_H
#define VGA_H

#include <stddef.h>
#include <stdint.h>

// Цвета VGA
enum VGAColor {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_PINK = 13,
    VGA_COLOR_YELLOW = 14,
    VGA_COLOR_WHITE = 15,
};

void vga_clear(void);
void vga_set_color(uint8_t fg, uint8_t bg);
void vga_set_cursor(uint8_t x, uint8_t y);
uint8_t vga_get_cursor_x(void);
uint8_t vga_get_cursor_y(void);
void vga_put_char(char c);
void vga_write(const char* str);
void vga_write_dec(uint32_t value);
void vga_write_hex(uint32_t value);
void vga_resetcolor(void);

#endif
