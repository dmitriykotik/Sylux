#ifndef CONSOLE_H
#define CONSOLE_H

#include <stddef.h>
#include <stdint.h>

enum ConsoleColor {
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGrey = 7,
    DarkGrey = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    Pink = 13,
    Yellow = 14,
    White = 15,
};

void Clear(void);
void SetColor(uint8_t ForegroundColor, uint8_t BackgroundColor);
void SetCursorPosition(uint8_t x, uint8_t y);
uint8_t GetCursorPositionX(void);
uint8_t GetCursorPositionY(void);
void PutChar(char c);
void Write(const char* str);
void WriteLine(const char* str);
void WriteDec(uint32_t value);
void WriteHex(uint32_t value);
void ResetColor(void);
void UpdateHardwareCursor(void);
void EnableCursor(int start, int end);
void DisableCursor(void);
void ReadLine(char* str, size_t maxLen);

#endif
