/* 
================================
- MP-DoS | Source
================================
- Автор: Плюха (Дмитрий Некраш) - https://www.youtube.com/@pluhaoff
- Файл: ./lib/logic.c
- Значение файла: Отвечает перед судом за микро логику
- Создан в: Kali Linux
================================
*/

#include "./logic.h"
#include "../drivers/lowlevel_io.h"
#include "../common.h"

int strcmp(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return 0; // Строки не равны
        }
        str1++;
        str2++;
    }
    // Если одна строка закончилась, а другая нет, они не равны
    if (*str1 != '\0' || *str2 != '\0') {
        return 0;
    }
    return 1; // Строки равны
}
