/* 
================================
- MP-DoS | Source
================================
- Автор: Плюха (Дмитрий Некраш) - https://www.youtube.com/@pluhaoff
- Файл: ./lib/inter.c
- Значение файла: Отвечает за задержки (sleep)
- Создан в: Kali Linux
================================
*/

#include "./inter.h"
#include "../drivers/lowlevel_io.h"
#include "../common.h"

void ksleep(int microseconds) {
    int counter;
    for (counter = 0; counter < microseconds; counter++) {
    }
}
