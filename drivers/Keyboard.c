#include <stdint.h>
#include <stdbool.h>
#include "../include/io.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_CMD_PORT  0x64

static bool shift = false;
static bool capslock = false;

static void SetLEDs(bool caps, bool num, bool scroll) {
    uint8_t leds = (scroll ? 1 : 0) | (num ? 2 : 0) | (caps ? 4 : 0);
    while (InByte(KEYBOARD_CMD_PORT) & 2);
    OutByte(KEYBOARD_DATA_PORT, 0xED);
    while (InByte(KEYBOARD_CMD_PORT) & 2);
    OutByte(KEYBOARD_DATA_PORT, leds);
}

static char GetChar(uint8_t sc, bool shift, bool caps) {
    static const char lower[] = {
        0,27,'1','2','3','4','5','6','7','8','9','0','-','=','\b',
        '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0,
        'a','s','d','f','g','h','j','k','l',';','\'','`',0,'\\',
        'z','x','c','v','b','n','m',',','.','/',0,'*',0,' ',0
    };
    static const char upper[] = {
        0,27,'!','@','#','$','%','^','&','*','(',')','_','+','\b',
        '\t','Q','W','E','R','T','Y','U','I','O','P','{','}','\n',0,
        'A','S','D','F','G','H','J','K','L',':','"','~',0,'|',
        'Z','X','C','V','B','N','M','<','>','?',0,'*',0,' ',0
    };
    if (sc >= sizeof(lower)) return 0;
    bool upperCase = (shift ^ caps);
    return upperCase ? upper[sc] : lower[sc];
}

char ReadChar() {
    static uint8_t lastScancode = 0;

    while (true) {
        uint8_t sc = InByte(KEYBOARD_DATA_PORT);

        if (sc == lastScancode) continue; // игнор повторов
        lastScancode = sc;

        bool released = sc & 0x80;
        uint8_t code = sc & 0x7F;

        // Модификаторы
        if (code == 42 || code == 54) { shift = !released; continue; }
        if (code == 58 && !released) {
            capslock = !capslock;
            SetLEDs(capslock, false, false);
            continue;
        }

        // Только нажатия
        if (!released) {
            char ch = GetChar(code, shift, capslock);
            if (ch) return ch;
        }
    }
}
