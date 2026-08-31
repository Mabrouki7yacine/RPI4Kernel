#include "uart.h"

void kernel_main(void) {
    gpio_uart_init();
    uart_init();
    write_str("Salam");
    write_str(" Alaikum\n\r");
    while (1);
}