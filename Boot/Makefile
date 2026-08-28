CC = aarch64-linux-gnu-gcc
LD = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy

CFLAGS = -std=c99 -ffreestanding -mgeneral-regs-only

all:
	$(CC) -c boot.s -o boot.o
	$(CC) $(CFLAGS) -c main.c
	$(LD) -nostdlib -T link.lds -o kernel.elf boot.o main.o
	$(OBJCOPY) -O binary kernel.elf kernel8.img

clean:
	rm -f *.o
	rm -f *.img
	rm -f *.elf