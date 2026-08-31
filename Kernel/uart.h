#ifndef UART_H
#define UART_H

#include "stdint.h"

#define UART0_BASE_ADDR 0xFE201000

#define UART_DATA_REG     0x00000000
#define UART_FLAG_REG     0x00000018
#define UART_CTRL_REG     0x00000030

#define UART_LINECTRL_REG 0x0000002C
#define UART_IRQ_MASK_REG 0x00000038

#define UART_IBRD_REG     0x00000024
#define UART_FBRD_REG     0x00000028

#define GPIO_BASE_ADDR   0xFE200000
#define GPIO_GPFSEL1     0x04

void uart_init(void);

void gpio_uart_init(void);

void write_char(char c);
void write_str(const char* str);

unsigned char read_char(void);

#endif