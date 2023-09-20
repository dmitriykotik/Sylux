# Sylux
Это простейшое ядро. Из пакета оно почти ничего не умеет. Автор будет продолжать доводить ядро до ума, но вы можете помочь в развитии проекта ядра Sylux. Напишите мне на почту, если хотите лично помогать в развитии проекта (на волонтёрской основе), или используйте "Pull requests" :D. 

> [!NOTE]
> Если у вас возникнут проблемы с компиляцией ядра, то отпишитесь мне на почту, я попробую помочь с проблемой, но не обещаю, что смогу.

> Почта: multiplayerdeveloper@gmail.com

> Автор: Плюха (Дмитрий Некраш) - https://www.youtube.com/@pluhaoff/

# Означение файлов и структура Sylux
- boot [folder] - Загрузчик ядра
  - bootsect.asm [file] - Загружает ядро в 32-х битном защищённом режиме
  - disk_load.asm [file] - Читает диск
  - gdt.asm [file] - Глобальная таблица дескриптеров
  - kernel_entry.asm [file] - Входная точка для ядра
  - print_hex.asm [file] - Вывод шестнадцатеричного числа на экран
  - print_string.asm [file] - Вывод строки на экран
  - print_string_pm.asm [file] - Вывод строки на экран в 32-х битном защищённом режиме
  - switch.asm [file] - Переключение в защищённый режим
- build [folder] - Сборщик
  - Makefile [file] - Файл сборки
- drivers [folder] - Драйвера
  - acpi_reboot.c [file] - Перезагрузка компьютера
  - acpi_reboot.h [file] 
  - keyboard.c [file] - Работа с клавиатурой
  - keyboard.h [file]
  - lowlevel_io.c [file] - Низкоуровневый доступ
  - lowlevel_io.h [file]
  - screen.c [file] - Работы с экраном
  - screen.h [file]
- include [folder] - Библиотеки
  - inter.c [file] - Библиотека прерываний
  - inter.h [file]
  - keyboard_drv.c [file] - Драйвер клавиатуры
  - keyboard_drv.h [file]
  - logic.c [file] - Логика (которой не существует :D)
  - logic.h [file]
- kernel [folder] - Ядро
  - dos.c [file] - Дос (по умолчанию не активно)
  - dos.h [file]
  - kernel.c [file] - Полузагрузчик. Что-то между загрузчиком и меню выбора ОС
- common.c [file] - Всякие полезные функции,константы и т.д.
- common.h [file]

# Необходимые инструменты
1. Linux (возможно, можно любой, но ядро собирается на kali linux полной сборки [Kali Linux | Everything](https://www.kali.org/get-kali/#kali-installer-images))
2. i386-elf-4.9.1-Linux-x86_64 - Скачайте от [сюда](https://disk.yandex.ru/d/eKocqL4wd-IfMg). Из архива переместите папку `itm` в папку `./build`. Если ссылка по каким либо причинам не работает, то загрузите компилятор вручную:
```
wget http://newos.org/toolchains/i386-elf-4.9.1-Linux-x86_64.tar.xz
mkdir /usr/local/i386elfgcc
tar -xf i386-elf-4.9.1-Linux-x86_64.tar.xz -C /usr/local/i386elfgcc --strip-components=1
export PATH=$PATH:/usr/local/i386elfgcc/bin
```
3. GCC => В комплекте c i386-elf-4.9.1-Linux-x86_64
4. LD => В комплекте c i386-elf-4.9.1-Linux-x86_64
5. NASM
6. QEMU - Установите так:
`sudo apt install qemu-kvm qemu`

# Загрузка, сборка и запуск
1. Скачиваем все инструменты выше.
2. (В идеале получаем рут права)
3. Скачиваем само ядро `git clone https://github.com/dmitriykotik/Sylux.git`
4. Редактируйте, что вам нужно или переходите сразу к 5 шагу
5. Переходим в папку build. Открываем в этой папке термина. И пишем: `make`
6. Таким образом у нас собирётся ядро и запустится в QEMU.
7. Если у вас не открылся QEMU с ядром, то попробуйте запустить в ручную: `qemu-system-i386 -fda sylux.bin`
> [!WARNING]  
> Если вы немного не понимаете как работает ядро, то это для вас: Если вы захотите создать новую папку в которой будут файлы (файлы на C языке конечно же) с зависимостями, то укажите эту папку в компиляции ядра. Тоесть, если в "make" файле прописанно `C_FILES = $(shell find ../kernel/*.c ../drivers/*.c ../*.c ../include/*.c)`, а вы хотите добавить папку "rabotaet_na_mena", то допишите папку так: `C_FILES = $(shell find ../kernel/*.c ../drivers/*.c ../*.c ../include/*.c ../rabotaet_na_mena/*.c)`, тоесть мы просто добавили `../rabotaet_na_mena/*.c`

> [!WARNING]
> Также, если вы хотите компилировать другой тип файлов, то нельзя указывать их в `C_FILES`! Также, если вы сменили расположение файла сборки, то тут всё сложнее.

> [!WARNING]
> Официальный сборщик ядра доступен только на Линукс, так что обращайте внимание на регистер слов!

> [!NOTE]
> Если у вас не получается скомпилировать ядро, или хотите сообщить о баге, то напишите мне на почту: `multiplayerdeveloper@gmail.com`

# Документация на текущие драйвера
> [!IMPORTANT]
> На данный момент (18.09.2023) документация может быть частично не доделана или полностью не доделана.

> [!NOTE]
> Если вы будете испортировать какую то библиотеку, то указывайте к ней путь ввиде: `../drivers/screen.h`.

## Driver ./drivers/screen.c

### kprint_colored
```C
void kprint_colored(u8 *str, u8 attr);
```
`u8 *str` - Отображаемый текст.

`u8 attr` - Код цветовой схемы.

Пример: 
```C
kprint_colored("Hello World!", 0x04);
```
Описание: Выводит текст в определённой цветовой схеме

> [!NOTE]
> Цветовую схему можно использовать как 0x Твет фона текста и Цвет текста. Например: В примере выше использовалась цветовая схема 0x04, тоесть чёрный фон текста и красный цвет текста, тоесть после 0x где 0 там чёрный цвет, а где 4 там красный. Снизу я напишу таблицу.

| Цветовая схема | Цвет | 
|:-----------|:----------------------------------------------:|
| 0 | Черный |
| 1 | Синий |
| 2 | Зеленый |
| 3 | Aqua |
| 4 | Красный |
| 5 | Сиреневый |
| 6 | Желтый |
| 7 | Белый |
| 8 | Серый |
| 9 | Светло-синий |
| а | Светло-зеленый |
| b | Легкая вода |
| с | Светло-красный |
| d | Светло-фиолетовый |
| e | Светло-желтый |
| f | Ярко-белый |

> [!NOTE]
> Взято с со статьи на сайте [Microsoft](https://learn.microsoft.com/ru-ru/windows-server/administration/windows-commands/color)

> [!IMPORTANT]
> Цветовая схема может не совпадать с реальной схемой!


### kwrite
```C
void kwrite(u8 *str);
```
`u8 *str` - Отображаемый текст.

Пример:
```C
kwrite("Hello world!");
```
Описание: Выводит текст с цветовой палитрой: Чёрный фон и серый текст


### kmessage
```C
void kmessage(u8 *str);
```
`u8 *str` - Отображаемый текст.

Пример:
```C
kmessage("Hello world!");
```
Описание: Выводит текст с цветовой палитрой: Белый фон и чёрный текст


### kprint
```C
void kprint(u8 *str);
```
`u8 *str` - Отображаемый текст.

Пример:
```C
kprint("Hello world!");
```
Описание: Выводит текст с цветовой палитрой: Чёрный фон и белый текст

> [!NOTE]
> Наверняка у вас задаётся вопрос. В чём различия между kprint, kwrite и kmessage? Ну, различия только в цветовой палитре. Если тяжело запомнить данные штуки, то советую по умолчанию использовать kwrite();


### kclear
```C
void kclear();
```
Пример:
```C
kclear();
```
Описание: Очищает весь экран.

## Driver ./drivers/keyboard.c
### kread
```C
void kread();
```
Пример:
```C
kread();
```
> [!NOTE]
> Почти во всех случаях указывается переменная для приёма данных. Следующий пример.

Пример №2:
```C
char *input = kread();
```
Описание: Принимает текст вводимый пользователем

## Driver ./drivers/acpi_reboot.c
### asm_reboot
```C
void asm_reboot();
```
Пример:
```C
asm_reboot();
```
Описание: Перезагружает компиютер на уровне ассемблера

## Library ./include/inter.c
### ksleep
```C
void ksleep(int microseconds);
```
`int microseconds` - Число в микросекундах

Пример:
```C
ksleep(5000000); // Приостановка в течении 5 секунд
```
Описание: Выполняет приостановку на определённое время в микросекундах

> [!IMPORTANT]
> Данный метод приостановки устарел!

## Library ./include/logic.c
### strcmp
```C
int strcmp(const char *str1, const char *str2);
```
`const char *str1` - Первый текст

`const char *str2` - Второй текст

Пример №1:
```C
return strcmp("1", "2");
```
`Returned`=> `0`

Пример №2:
```C
#include "../drivers/screen.h"
<...>
if (strcmp("123", "123") == 1){
  kprint("true");
}else{
  kprint("false");
}
```
`Returned`=> `true`

Пример №3:
```C
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
<...>
char *input = kread();
```
`kread()` <= `"User"`
```C
if (strcmp(input, "User") == 1){
  kprint("true");
}else{
  kprint("false");
}
```
`Returned`=> `true`

Описание: Метод проверяет совпадение двух строк. Если первая строка равна второй строке, то возврат будет `1`. В первом примере мы просто проводим опрос двух строк и возвращаем значение 0, так как строки не равны. Во втором примере мы уже используем опрос в структуре `if`. Делаем опрос двух строк и структура возвращает значение `1`, тоесть равно. С помощью конструкции `if` проверяем, `есть совпадения?`, так как совпадения есть, то возвращаем значение true. В 3-м примере почти всё также как и во 2-м. Только в 3-м мы используем получение ввода пользователя, и проверяем, что он ввёл.

## Library ./include/keyboard_drv.c
### kbdus
```C
char kbdus[128];
```
Описание: Это переменная в которой хранится английская раскладка клавиатуры.

### init_keyboard
```C
void init_keyboard();
```
Описание: Инициализация клавиатуры

### read_keyboard
```C
char read_keyboard();
```
Описание: Чтение нажатия клавиатуры, после выбираем символ из kbdus и возвращаем его.

### clear_char
```C
void clear_char(u16 offset);
```
Описание: Удаление определённого символа
