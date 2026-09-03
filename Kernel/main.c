#include "print.h"
#include "uart.h"

void kernel_main(void) {
    gpio_uart_init();
    uart_init();
    LOGI("GPIO", "Rx Tx GPIO init succesfully");
    LOGI("UART", "Initialized at %u baud", 115200);
    LOGI("Kernel", "Salam Alaikum");
    LOGW("Kernel", "There is noting we can do");
    LOGE("Kernel", "Bye");
    while (1);
}