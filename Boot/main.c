#include "uart.h"

void kernel_main(void) {
    uart_init();
    write_str("Salam");
    while (1);
}