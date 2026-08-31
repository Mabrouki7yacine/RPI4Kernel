#ifndef LIB_H
#define LIB_H

#include "stdint.h"

uint32_t load_word(uint64_t address);
void store_word(uint64_t address, uint32_t value);
void delay(uint64_t address);

#endif