#include "vga.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000

static uint16_t* const vga_buffer = (uint16_t*) VGA_ADDRESS;
static uint8_t cursor_row = 0;
static uint8_t cursor_col = 0;
static uint8_t vga_color = 0x0F; // Белый текст на чёрном фоне

static uint16_t make_vga_entry(char c, uint8_t color) {
    return (uint16_t)c | ((uint16_t)color << 8);
}

void vga_set_color(uint8_t fg, uint8_t bg) {
    vga_color = (bg << 4) | (fg & 0x0F);
}

void vga_set_cursor(uint8_t x, uint8_t y) {
    if (x < VGA_WIDTH && y < VGA_HEIGHT) {
        cursor_col = x;
        cursor_row = y;
    }
}

uint8_t vga_get_cursor_x(void) {
    return cursor_col;
}

uint8_t vga_get_cursor_y(void) {
    return cursor_row;
}

void vga_clear(void) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            vga_buffer[index] = make_vga_entry(' ', vga_color);
        }
    }
    cursor_row = 0;
    cursor_col = 0;
}

void vga_put_char(char c) {
    if (c == '\n') {
        cursor_col = 0;
        cursor_row++;
        if (cursor_row >= VGA_HEIGHT) cursor_row = 0;
        return;
    }

    const size_t index = cursor_row * VGA_WIDTH + cursor_col;
    vga_buffer[index] = make_vga_entry(c, vga_color);
    cursor_col++;
    if (cursor_col >= VGA_WIDTH) {
        cursor_col = 0;
        cursor_row++;
        if (cursor_row >= VGA_HEIGHT) cursor_row = 0;
    }
}

void vga_write(const char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        vga_put_char(str[i]);
    }
}

void vga_write_dec(uint32_t value) {
    char buffer[11]; // max 4294967295 + '\0'
    int i = 0;

    if (value == 0) {
        vga_put_char('0');
        return;
    }

    while (value > 0) {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }

    for (int j = i - 1; j >= 0; j--) {
        vga_put_char(buffer[j]);
    }
}

void vga_write_hex(uint32_t value) {
    vga_write("0x");

    for (int i = 28; i >= 0; i -= 4) {
        uint8_t digit = (value >> i) & 0xF;
        if (digit < 10) {
            vga_put_char('0' + digit);
        } else {
            vga_put_char('A' + digit - 10);
        }
    }
}

void vga_resetcolor(void) {
    vga_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}
