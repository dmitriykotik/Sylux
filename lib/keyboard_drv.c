/* 
================================
- MP-DoS | Source
================================
- Автор: Плюха (Дмитрий Некраш) - https://www.youtube.com/@pluhaoff
- Файл: ./lib/keyboard_drv.c
- Значение файла: Тут прописана основная механика для библиотеки ./drivers/keyboard.c (./drivers/keyboard.h)
- Создан в: Kali Linux
================================
*/

#include "../drivers/screen.h"
#include "./keyboard_drv.h"
#include "../drivers/lowlevel_io.h"
#include "../common.h"

char kbdus[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*',
    0, ' ',
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
    '-', 0, 0, 0, '+', 0, 0, 0,
    0, 0, 0,
    0,
    0, 0, 0,
    0, 0, 0,
    0,
    0, 0, 0, 0, 0, 0,
    0, 0, 0,
    0,
};

void init_keyboard() {
    port_byte_out(0x64, 0xAE);
    port_byte_out(0x64, 0x20);
    u8 status = port_byte_in(0x60);
    status |= 0x01;
    status &= ~0x02;
    port_byte_out(0x64, 0x60);
    port_byte_out(0x60, status);
}

char read_keyboard() {
    while (1) {
        if (port_byte_in(0x64) & 0x01) {
            char scancode = port_byte_in(0x60);
            if (scancode < 128) {
                return kbdus[scancode];
            }
        }
    }
}

void clear_char(u16 offset) {
    write(' ', WHITE_ON_BLACK, offset);
    set_cursor(offset);
}
