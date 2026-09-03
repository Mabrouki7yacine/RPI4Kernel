#include "print.h"
#include "stdarg.h"
#include "stdbool.h"
#include "uart.h"

static uint32_t copy_string(char* dest_str, int position, char* src_str) {
    uint32_t index = 0;
    while (index < 1024 && src_str[index] != '\0')
    {
        dest_str[index + position] = src_str[index];
        index++;
    }
    return index;
}

static int32_t hex_to_string(char* dest_str, int position, uint32_t hex) {
    char digits_buffer[25];
    char digits_map[16] = "0123456789ABCDEF";
    int size = 0;

    do {
        digits_buffer[size++] = digits_map[hex % 16];
        hex /= 16;
    } while(hex != 0);

    for (int i = size - 1; i >= 0; i--) {
        dest_str[position++] = digits_buffer[i];
    }

    return size;
}

static int32_t uint_to_string(char* dest_str, int position, uint32_t uinteger) {
    char digits_buffer[25];
    char digits_map[10] = "0123456789";
    int size = 0;

    do {
        digits_buffer[size++] = digits_map[uinteger % 10];
        uinteger /= 10;
    } while(uinteger != 0);

    for (int i = size - 1; i >= 0; i--) {
        dest_str[position++] = digits_buffer[i];
    }
    
    return size;
}

static int32_t int_to_string(char* dest_str, int position, int32_t integer) {
    char digits_buffer[25];
    char digits_map[10] = "0123456789";
    int size = 0;
    bool negative = false;

    if (integer < 0) {
        integer = -integer;
        dest_str[position++] = '-';
        negative = true;
    }

    do {
        digits_buffer[size++] = digits_map[integer % 10];
        integer /= 10;
    } while (integer != 0);

    for (int i = size - 1; i >= 0; i--) {
        dest_str[position++] = digits_buffer[i];
    }
    
    if (negative) {
        size++;
    }

    return size;
}

int32_t printk(const char *format, ...) {
    char buff[1024];
    int32_t size = 0;
    int64_t integer = 0;
    char *string = 0;
    va_list args;

    va_start(args, format);

    for (uint32_t i = 0; i < 1024 && format[i] != '\0'; i++) {
        if (format[i] != '%') {
            buff[size++] = format[i];
        } else {
            switch (format[++i])
            {
                case 'x':
                    integer = (int64_t) va_arg(args, uint32_t);
                    size += hex_to_string(buff, size, (uint32_t) integer);
                    break;

                case 'u':
                    integer = (int64_t) va_arg(args, uint32_t);
                    size += uint_to_string(buff, size, (uint32_t) integer);
                    break;

                case 'd':
                    integer = (int64_t) va_arg(args, int32_t);
                    size += int_to_string(buff, size, (int32_t) integer);
                    break;

                case 's':
                    string = va_arg(args, char*);
                    size += copy_string(buff, size, string);
                    break;

                case 'c':
                    buff[size++] = (char)va_arg(args, int);
                    break;

                case '%':
                    buff[size++] = '%';
                    break;
                
                default:
                    break;
            }
        }
        
    }
    buff[size] = '\0';
    write_str(buff);

    va_end(args);
    return size;
}