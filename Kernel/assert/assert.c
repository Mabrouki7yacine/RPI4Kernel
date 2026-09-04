#include "assert.h"
#include "../print.h"

void print_error(char* filename, uint64_t line) {
    printk("\r\nAssertion Failed [%s: %u]\r\n", filename, line);

    while (1) { }
}