CC = aarch64-linux-gnu-gcc
LD = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy

BUILD = build/

CFLAGS = -std=c99 -ffreestanding -mgeneral-regs-only

all:
	mkdir -p $(BUILD)

	$(CC) -c boot.s -o $(BUILD)boot.o
	$(CC) -c util/lib.s  -o $(BUILD)lib_s.o

	$(CC) $(CFLAGS) -c main.c -o $(BUILD)main.o
	$(CC) $(CFLAGS) -c util/lib.c -o $(BUILD)lib_c.o
	$(CC) $(CFLAGS) -c print.c -o $(BUILD)print.o
	$(CC) $(CFLAGS) -c uart.c -o $(BUILD)uart.o

	$(LD) -nostdlib -T link.lds \
		-o $(BUILD)kernel.elf \
		$(BUILD)boot.o \
		$(BUILD)main.o \
		$(BUILD)uart.o \
		$(BUILD)print.o \
		$(BUILD)lib_c.o \
		$(BUILD)lib_s.o

	$(OBJCOPY) -O binary \
		$(BUILD)kernel.elf \
		$(BUILD)my_kernel.img

clean:
	rm -rf $(BUILD)
