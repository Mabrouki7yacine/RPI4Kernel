#include "uart.h"
#include "lib.h"

void uart_init(void) {
    uint64_t address = UART0_BASE_ADDR + UART_CTRL_REG;
    store_word(address, 0); // Disable UART

    address = UART0_BASE_ADDR + UART_LINECTRL_REG;
    uint32_t lcrh = 0;
    store_word(address, lcrh); // Flush FIFO

    lcrh |= (0b11 << 5); // 8 bit data
    lcrh |= (0b1  << 4); // FIFO Enable
    store_word(address, lcrh); // 1 stop bit, No parity

    address = UART0_BASE_ADDR + UART_IBRD_REG;
    store_word(address, 26); // BAUDDIV = (48 × 1000 × 1000) / (16 × 115200)

    address = UART0_BASE_ADDR + UART_FBRD_REG;
    store_word(address, 3); // BAUDDIV = 26.041666...

    address = UART0_BASE_ADDR + UART_IRQ_MASK_REG;
    store_word(address, 0); // Disable Interrupt

    address = UART0_BASE_ADDR + UART_CTRL_REG;
    uint32_t ctrl = 0;
    ctrl |= (0b1  << 9); // RX Enable
    ctrl |= (0b1  << 8); // TX Enable
    ctrl |= (0b1  << 0); // UART Enable
    store_word(address, ctrl); // Enable UART

}

void write_char(char c) {
    while (load_word(UART0_BASE_ADDR + UART_FLAG_REG) & (1 << 5));
    store_word(UART0_BASE_ADDR + UART_DATA_REG, c);
}

void write_str(const char* str) {
    for (uint8_t i = 0; i < 64 || str[i] != '\0'; i++) {
        write_char(str[i]);
    }
}

unsigned char read_char(void) {
    while (load_word(UART0_BASE_ADDR + UART_FLAG_REG) & (1 << 4));
    uint32_t recv = load_word(UART0_BASE_ADDR + UART_DATA_REG);
    return recv & 0xFF;
}