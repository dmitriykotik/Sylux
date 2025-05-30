﻿;
;  __  __       _             _____       _
; |  \/  |     | |       _   / ____|     | |
; | \  / | __ _| | _____(_) | (___  _   _| |_   ___  __
; | |\/| |/ _` | |/ / _ \    \___ \| | | | | | | \ \/ /
; | |  | | (_| |   <  __/_   ____) | |_| | | |_| |>  <
; |_|  |_|\__,_|_|\_\___(_) |_____/ \__, |_|\__,_/_/\_\
;                                    __/ |
;                                   |___/
;
; Specify the path to the compiler. If you have not installed the compiler, you can install it,
; as well as other necessary packages, using the ./Make install_i686 command
[Compiler]
i686-elf-tools = i686-elf-tools

; Make sure that the qemu folder you specify contains tools such as: qemu-system-x86_64.
; If the tools can be used without specifying the full path, leave this field blank
[Debug]
qemu = qemu-system-x86_64

; Specify the data for the output files
[Output]
bin = build/boot/sylux.bin
iso = sylux.iso

; Section for user variables.
; After entering the %i686-elf-tools% variable, do not enter a slash, it will be supplied if necessary.
; I.e. specify the string as follows: %i686-elf-tools%i686-elf-gcc <...>
; Enter the identifier for your variable, and after through the equals sign, enter the value without the quotation marks.
; You can then use this variable as follows: %your_variable%
[Vars]
gcc = bin/i686-elf-gcc
as = bin/i686-elf-as
linker = linker/linker.ld

; Assembly Section.
; Specify the number of commands to be executed, and name the variables with these commands in numerical order (i.e. 1, 2, 3, etc.). The countdown starts at 1.
; While compiling with grub-mkrescue make sure you have the xorriso package installed, if not you can install it with ./Make install_i686
[Build]
Count = 12
1 = echo -= Assembly... =-
2 = echo Clearing...
3 = ./Make clean
4 = echo Assembling boot...
5 = ./%i686-elf-tools%/%as% boot/boot.s -o boot/boot.o
6 = echo Assembling kernel...
7 = foreach gcc ./%i686-elf-tools%/%gcc% -c %*%.c -o %*%.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
8 = echo Linking...
9 = foreach ld ./%i686-elf-tools%/%gcc% -T %linker% -o %bin% -ffreestanding -O2 -nostdlib %*%
10 = echo Creating an image with GRUB boot loader...
11 = grub-mkrescue -o %iso% build/
12 = echo -= Assembly complete! =-

; Launch Section.
; Specify the number of commands to be executed, and name the variables with these commands in numerical order (i.e. 1, 2, 3, etc.). The countdown starts at 1.
[Run]
Count = 2
1 = echo -= Launch... =-
2 = %qemu% -cdrom %iso%

; Clean Section.
; Specify the number of commands to be executed, and name the variables with these commands in numerical order (i.e. 1, 2, 3, etc.). The countdown starts at 1.
[Clean]
Count = 7
1 = echo -= Clearing... =-
2 = echo Deleting assembly files...
3 = foreach output rm %*%.o
5 = rm %bin%
6 = rm %iso%
8 = echo -= Cleanup complete! =-
