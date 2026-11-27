
ASM = nasm
CC = i686-elf-gcc
LD = i686-elf-ld
OBJCOPY = i686-elf-objcopy

BOOTSTRAP_FILE = bootstrap.asm
INIT_KERNEL_FILES = starter.asm
KERNEL_FILES = main.c
KERNEL_FLAGS = -std=c2x -Wall -m32 -c -ffreestanding -fno-asynchronous-unwind-tables -fno-pie
KERNEL_OBJECT = -o kernel.elf

.PHONY: build clean run

build: kernel.img

kernel.img: $(BOOTSTRAP_FILE) $(INIT_KERNEL_FILES) $(KERNEL_FILES)
	$(ASM) -f bin $(BOOTSTRAP_FILE) -o bootstrap.o
	$(ASM) -f elf32 $(INIT_KERNEL_FILES) -o starter.o
	$(CC) $(KERNEL_FLAGS) $(KERNEL_FILES) $(KERNEL_OBJECT)
	$(CC) $(KERNEL_FLAGS) screen.c -o screen.elf
	$(CC) $(KERNEL_FLAGS) process.c -o process.elf
	$(CC) $(KERNEL_FLAGS) scheduler.c -o scheduler.elf
	$(CC) $(KERNEL_FLAGS) heap.c -o heap.elf
	$(CC) $(KERNEL_FLAGS) paging.c -o paging.elf
	
	$(LD) -Tlinker.ld starter.o kernel.elf screen.elf process.elf scheduler.elf heap.elf paging.elf -o ArsenalKernel.elf
	$(OBJCOPY) -O binary ArsenalKernel.elf ArsenalKernel.bin
	dd if=bootstrap.o of=kernel.img
	dd seek=1 conv=sync if=ArsenalKernel.bin of=kernel.img bs=512 count=50
	dd seek=51 conv=sync if=/dev/zero of=kernel.img bs=512 count=2001

run: kernel.img
	#qemu-system-x86_64 -s -drive format=raw,file=kernel.img
	qemu-system-x86_64 -s kernel.img -display cocoa,zoom-to-fit=on
	#qemu-system-i386 -d int,cpu_reset -no-reboot -drive format=raw,file=kernel.img


clean:
	rm -f *.o *.elf *.bin *.img
	
	
	
	
	
	
	
	
	
	
	
	
	
	




