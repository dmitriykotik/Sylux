#include "Console.h"
#include "Keyboard.h"
#include "../include/io.h"

#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 25
#define CONSOLE_ADDRESS 0xB8000

#define PORT_COMMAND 0x3D4
#define PORT_DATA    0x3D5

static uint16_t* const buffer = (uint16_t*) CONSOLE_ADDRESS;
static uint8_t cursor_row = 0;
static uint8_t cursor_col = 0;
static uint8_t color = 0x0F;

static uint16_t Make_Entry(char c, uint8_t color) {
    return (uint16_t)c | ((uint16_t)color << 8);
}

void Clear(void) {
    for (size_t y = 0; y < CONSOLE_HEIGHT; y++) {
        for (size_t x = 0; x < CONSOLE_WIDTH; x++) {
            const size_t index = y * CONSOLE_WIDTH + x;
            buffer[index] = Make_Entry(' ', color);
        }
    }
    cursor_row = 0;
    cursor_col = 0;
}

void SetColor(uint8_t ForegroundColor, uint8_t BackgroundColor) {
    color = (BackgroundColor << 4) | (ForegroundColor & 0x0F);
}

void SetCursorPosition(uint8_t x, uint8_t y) {
    if (x < CONSOLE_WIDTH && y < CONSOLE_HEIGHT) {
        cursor_col = x;
        cursor_row = y;
    }
}

uint8_t GetCursorPositionX(void) {
    return cursor_col;
}

uint8_t GetCursorPositionY(void) {
    return cursor_row;
}

void PutChar(char c) {
    if (c == '\n') {
        cursor_col = 0;
        cursor_row++;
        if (cursor_row >= CONSOLE_HEIGHT) cursor_row = 0;
        UpdateHardwareCursor();
        return;
    }

    const size_t index = cursor_row * CONSOLE_WIDTH + cursor_col;
    buffer[index] = Make_Entry(c, color);
    cursor_col++;
    if (cursor_col >= CONSOLE_WIDTH) {
        cursor_col = 0;
        cursor_row++;
        if (cursor_row >= CONSOLE_HEIGHT) cursor_row = 0;
    }
    UpdateHardwareCursor();
}

void Write(const char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        PutChar(str[i]);
        UpdateHardwareCursor();
    }
}

void WriteLine(const char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        PutChar(str[i]);
        UpdateHardwareCursor();
    }
    PutChar('\n');
    UpdateHardwareCursor();
}

void WriteDec(uint32_t value) {
    char buffer[11];
    int i = 0;

    if (value == 0) {
        PutChar('0');
        UpdateHardwareCursor();
        return;
    }

    while (value > 0) {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }

    for (int j = i - 1; j >= 0; j--) {
        PutChar(buffer[j]);
        UpdateHardwareCursor();
    }
}

void WriteHex(uint32_t value) {
    Write("0x");

    for (int i = 28; i >= 0; i -= 4) {
        uint8_t digit = (value >> i) & 0xF;
        if (digit < 10) {
            PutChar('0' + digit);
            UpdateHardwareCursor();
        } else {
            PutChar('A' + digit - 10);
            UpdateHardwareCursor();
        }
    }
}

void ResetColor(void) {
    SetColor(White, Black);
}

void UpdateHardwareCursor(void) {
    uint16_t pos = cursor_row * CONSOLE_WIDTH + cursor_col;
    OutByte(PORT_COMMAND, 0x0F);
    OutByte(PORT_DATA, (uint8_t)(pos & 0xFF));
    OutByte(PORT_COMMAND, 0x0E);
    OutByte(PORT_DATA, (uint8_t)((pos >> 8) & 0xFF));
}

void EnableCursor(int start, int end) {
    if (start <= -1) start = 14;
    if (end <= -1) end = 15;
    OutByte(PORT_COMMAND, 0x0A);
    OutByte(PORT_DATA, (InByte(PORT_DATA) & 0xC0) | start);
    OutByte(PORT_COMMAND, 0x0B);
    OutByte(PORT_DATA, (InByte(PORT_DATA) & 0xE0) | end);
}

void DisableCursor(void) {
    OutByte(PORT_COMMAND, 0x0A);
    OutByte(PORT_DATA, 0x20);
}

void ReadLine(char* str, size_t maxLen) {
    size_t index = 0;

    while (index < maxLen - 1) {
        char c = ReadChar();

        if (c == '\b') {
            if (index > 0) {
                index--;
                if (cursor_col > 0) cursor_col--;
                else if (cursor_row > 0) {
                    cursor_row--;
                    cursor_col = CONSOLE_WIDTH - 1;
                }
                PutChar(' ');
                cursor_col--;
                UpdateHardwareCursor();
            }
        } else if (c == '\n') {
            PutChar('\n');
            break;
        } else {
            str[index++] = c;
            PutChar(c);
        }
    }

    str[index] = '\0';
}