We will build a **bare-metal kernel for the Raspberry Pi 4**.

We will not write our own bootloader because the BCM2711 boot process starts with the VideoCore GPU while the ARM cores remain inactive. The Raspberry Pi firmware handles the early boot process, initializes the system, loads our `kernel8.img` into memory, and then starts the ARM core at our kernel entry point.
