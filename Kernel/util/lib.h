#ifndef LIB_H
#define LIB_H

#include "stdint.h"
#include <stddef.h>

uint32_t load_word(uint64_t address);
void store_word(uint64_t address, uint32_t value);
void delay(uint64_t address);

void *memset(void *ptr, int value, size_t num);
void *memcpy(void *dest, const void *src, size_t count);
int memcmp(const void *a, const void *b, size_t count);

#endif