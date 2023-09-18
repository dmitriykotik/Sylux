# Sylux
Это простейшое ядро. Из пакета оно почти ничего не умеет. Автор будет продолжать доводить ядро до ума, но вы можете помочь в развитии проекта ядра Sylux. Напишите мне на почту, если хотите лично помогать в развитии проекта (на волонтёрской основе), или используйте "Pull requests" :D. 

Если у вас возникнут проблемы с компиляцией ядра, то отпишитесь мне на почту, я попробую помочь с проблемой, но не обещаю, что смогу.

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
  - itm [folder] - Встроенный компилятор (gcc, ld) (без nasm и qemu)
    - bin [folder]
      - <...>
    - i386-elf [folder]
      - <...>
    - include [folder]
      - <...>
    - lib [folder]
      - <...>
    - libexec [folder]
      - <...>
    - share [folder]
      - <...>
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
2. GCC => В комплекте. Если не работает инструмент из коробки, то попробуйте скачать так:
```
wget http://newos.org/toolchains/i386-elf-4.9.1-Linux-x86_64.tar.xz
mkdir /usr/local/i386elfgcc
tar -xf i386-elf-4.9.1-Linux-x86_64.tar.xz -C /usr/local/i386elfgcc --strip-components=1
export PATH=$PATH:/usr/local/i386elfgcc/bin
```
4. LD => В комплекте.
5. NASM
6. QEMU - Установите так:
`sudo apt install qemu-kvm qemu`

#Загрузка, сборка и запуск
1. Скачиваем все инструменты выше.
2. (В идеале получаем рут права)
3. Скачиваем само ядро `git clone https://github.com/dmitriykotik/Sylux.git`
4. Редактируйте, что вам нужно или переходите сразу к 5 шагу
5. Переходим в папку build. Открываем в этой папке термина. И пишем: `make`
6. Таким образом у нас собирётся ядро и запустится в QEMU.
6.1. Если у вас не открылся QEMU с ядром, то попробуйте запустить в ручную: `qemu-system-i386 -fda sylux.bin`
> [!WARNING]  
> Critical content demanding immediate user attention due to potential risks.
