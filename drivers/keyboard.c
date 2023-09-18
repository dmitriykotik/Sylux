/* 
================================
- MP-DoS | Source
================================
- Автор: Плюха (Дмитрий Некраш) - https://www.youtube.com/@pluhaoff
- Файл: ./drivers/keyboard.c
- Значение файла: Методы для работы с клавиатурой
- Создан в: Kali Linux
================================
*/

#include "./keyboard.h"
#include "../lib/keyboard_drv.h"
#include "./screen.h"
#include "./lowlevel_io.h"
#include "../common.h"

char *kread(){
	char input_buffer[256];
	u8 buffer_index = 0;
	int active = 1;
	init_keyboard();
    	while (active) {
       		char key = read_keyboard();
        	if (key == '\n') {
            		input_buffer[buffer_index] = '\0';
            		buffer_index = 0;
            		active = 0;
            		kprint("\n");
            		return(input_buffer);
        	} 
        	else if (key == '\b') {
            		if (buffer_index > 0) {
                		buffer_index--;
                		u16 offset = get_cursor();
                		offset -= 2;
                		clear_char(offset);
                		input_buffer[buffer_index] = '\0';
            		}
        	} 
        	else if (key != 0) {
            		if (buffer_index < sizeof(input_buffer) - 1) {
                		input_buffer[buffer_index] = key;
                		buffer_index++;
                		putchar(key, WHITE_ON_BLACK);
            		}
        	}
    	}
}
