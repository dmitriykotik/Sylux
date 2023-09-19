/* 
================================
- MP-DoS | Source
================================
- Автор: Плюха (Дмитрий Некраш) - https://www.youtube.com/@pluhaoff
- Файл: ./kernel/kernel.c
- Значение файла: Это БУТ "меню" (ну или SBT (Sylux Boot Terminal))
- Создан в: Kali Linux
================================
*/


//include "../include/logic.h"
//#include "../drivers/keyboard.h"
//#include "../drivers/acpi_reboot.h"
//#include "./dos.h"


#include "../common.h"
#include "../drivers/screen.h"

s32		kmain()
{	
	kclear();
	kmessage("Welcome to SBT!\n\n");
	kprint("Please, select OS:\n");
	
	
	
	/* Так можно реализовать запуск операционной сисетмы под Sylux */
	/*
	char *os = "\n1. MP-DoS\n2. MP-DoS | Secure Mode\n";
	kprint(os);
	int sel1 = 1;
	while (sel1){
		kprint("> ");
		char *inp = kread();
		if (strcmp(inp, "1") == 1){
			sel1 = 0;
			kernel_start(); //Метод запуска содержащийся в файле dos.c
			
		}
		else if (strcmp(inp, "2") == 1){
			sel1 = 0;
			kernel_secure_start(); //Метод запуска защищённого режима содержащийся в файле dos.c
		}
		else if (strcmp(inp, "list") == 1){
			kprint(os);
		}
		else if (strcmp(inp, "reboot") == 1){
			asm_reboot();
		}	
		else if (strcmp(inp, "help") == 1){
			kprint("\n1. (number) - Operating System selection\n2. list - Output of all operating systems\n3. reboot - Computer restart\n4. help - Reference\n\n");
		}
		else{
			kprint_colored("There is no operating system under that number!\n", 0x04);
		}
	}
	*/
	
	return 0;
}

