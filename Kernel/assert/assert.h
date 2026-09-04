#ifndef ASSERT_H
#define ASSERT_H

#include "stdint.h"

#define assert(e)       \
    do{                 \
        if (!e) {       \
            print_error(__FILE__, __LINE__);  \
        }               \
    } while (0)

void print_error(char* filename, uint64_t line);

#endif