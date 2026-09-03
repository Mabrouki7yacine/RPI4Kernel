#include "uart.h"
#include "util/lib.h"

void gpio_uart_init(void)
{
    uint64_t address = GPIO_BASE_ADDR + GPIO_GPFSEL1;

    uint32_t value = load_word(address);

    // Clear GPIO14 and GPIO15 function bits
    value &= ~((0b111 << 12) | (0b111 << 15));

    // GPIO14 = ALT0 (TXD0)
    // GPIO15 = ALT0 (RXD0)
    value |= (0b100 << 12);
    value |= (0b100 << 15);

    store_word(address, value);
}

void uart_init(void)
{
    // Disable UART
    store_word(UART0_BASE_ADDR + UART_CTRL_REG, 0);

    // Wait until UART is not busy
    while (load_word(UART0_BASE_ADDR + UART_FLAG_REG) & (1 << 3));

    // Disable FIFO / flush it
    store_word(UART0_BASE_ADDR + UART_LINECTRL_REG, 0);

    // Baud rate: 48 MHz -> 115200
    store_word(UART0_BASE_ADDR + UART_IBRD_REG, 26);
    store_word(UART0_BASE_ADDR + UART_FBRD_REG, 3);

    // 8 data bits + FIFO
    uint32_t lcrh = 0;
    lcrh |= (0b11 << 5);
    lcrh |= (1 << 4);

    // IMPORTANT: write LCRH AFTER IBRD/FBRD
    store_word(UART0_BASE_ADDR + UART_LINECTRL_REG, lcrh);

    // Disable UART interrupts
    store_word(UART0_BASE_ADDR + UART_IRQ_MASK_REG, 0);

    // RX + TX + UART
    uint32_t ctrl = 0;
    ctrl |= (1 << 9);
    ctrl |= (1 << 8);
    ctrl |= (1 << 0);

    store_word(UART0_BASE_ADDR + UART_CTRL_REG, ctrl);
}

void write_char(char c) {
    while (load_word(UART0_BASE_ADDR + UART_FLAG_REG) & (1 << 5));
    store_word(UART0_BASE_ADDR + UART_DATA_REG, c);
}

void write_str(const char* str) {
    for (uint32_t i = 0; i < 1024 && str[i] != '\0'; i++) {
        write_char(str[i]);
    }
}

unsigned char read_char(void) {
    while (load_word(UART0_BASE_ADDR + UART_FLAG_REG) & (1 << 4));
    uint32_t recv = load_word(UART0_BASE_ADDR + UART_DATA_REG);
    return recv & 0xFF;
}