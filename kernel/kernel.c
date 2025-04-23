#include <stdbool.h>
#include "../drivers/Console.h"
#include "../include/string.h"

void kernel_main(void) {
    WriteLine("Starting Sylux...");
    while (true) {
        char input[128];
        Write("> ");
        ReadLine(input, sizeof(input));

        if (strcmp(input, "clear") == 0)
            Clear();
        else if (strcmp(input, "cur_enable") == 0) {
            EnableCursor(-1, -1);
            UpdateHardwareCursor();
        }
        else if (strcmp(input, "cur_disable") == 0)
            DisableCursor();
        else if (strcmp(input, "help") == 0){
            WriteLine("clear\ncur_enable\ncur_disable");
        }
    }
}

