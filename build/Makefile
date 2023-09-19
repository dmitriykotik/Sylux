C_FILES = $(shell find ../kernel/*.c ../drivers/*.c ../*.c ../include/*.c)
temp = $(notdir $(C_FILES))
O_FILES = ${temp:.c=.o}
CFLAGS = -g

run: sylux.bin
	qemu-system-i386 -fda sylux.bin

debug: sylux.bin kernel.elf
	qemu-system-i386 -s -S -fda sylux.bin

sylux.bin: bootsect.bin kernel.bin
	cat bootsect.bin kernel.bin > sylux.bin

bootsect.bin:
	cd ../boot/ && nasm bootsect.asm -f bin -o ../build/bootsect.bin && cd -

kernel.bin: kernel_entry.o kernel.o
	./itm/bin/i386-elf-ld -o kernel.bin -Ttext 0x1000 kernel_entry.o $(O_FILES) --oformat binary

kernel_entry.o:
	nasm ../boot/kernel_entry.asm -f elf -o kernel_entry.o

kernel.o:
	./itm/bin/i386-elf-gcc ${CFLAGS} -ffreestanding -c $(C_FILES)

kernel.elf: kernel_entry.o kernel.o 
	./itm/bin/i386-elf-ld -o kernel.bin -Ttext 0x1000 kernel_entry.o $(O_FILES) -o kernel.elf

clean:
	rm *.bin *.o *.elf
