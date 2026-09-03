#ifndef PRINT_H
#define PRINT_H

#include "stdint.h"

#define MY_LOG_COLOR_E  "\033[0;31m" // Red
#define MY_LOG_COLOR_W  "\033[0;33m" // Yellow
#define MY_LOG_COLOR_I  "\033[0;32m" // Green
#define MY_LOG_RESET    "\033[0m"

int32_t printk(const char *format, ...);

#define LOGE(tag, ...)                          \
    do {                                        \
        printk(MY_LOG_COLOR_E "[%s] ERROR: ", tag); \
        printk(__VA_ARGS__);                    \
        printk(MY_LOG_RESET "\r\n");            \
    } while (0)

#define LOGW(tag, ...)                          \
    do {                                        \
        printk(MY_LOG_COLOR_W "[%s] WARN: ", tag);  \
        printk(__VA_ARGS__);                    \
        printk(MY_LOG_RESET "\r\n");            \
    } while (0)

#define LOGI(tag, ...)                          \
    do {                                        \
        printk(MY_LOG_COLOR_I "[%s] INFO: ", tag);  \
        printk(__VA_ARGS__);                    \
        printk(MY_LOG_RESET "\r\n");            \
    } while (0);

#endif