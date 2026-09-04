#include "lib.h"

void *memset(void *ptr, int value, size_t num) {
    uint8_t *dest = (uint8_t *)ptr;
    uint8_t byte = (uint8_t)value;

    for (size_t i = 0; i < num; i++) {
        dest[i] = byte;
    }

    return ptr;
}

int memcmp(const void *a, const void *b, size_t count) {
    const uint8_t *ptr_a = (const uint8_t *)a;
    const uint8_t *ptr_b = (const uint8_t *)b;

    for (size_t i = 0; i < count; i++) {
        if (ptr_a[i] != ptr_b[i]) {
            return ptr_a[i] - ptr_b[i];
        }
    }

    return 0;
}

void *memcpy(void *dest, const void *src, size_t count) {

    if ((((uintptr_t)dest | (uintptr_t)src) & 7) == 0) {
        uint64_t *ptr64_dest = (uint64_t *)dest;
        const uint64_t *ptr64_src = (const uint64_t *)src;

        for (size_t i = 0; i < count / 8; i++) {
            ptr64_dest[i] = ptr64_src[i];
        }

        size_t start = count & ~((size_t)7); // FFFFFFFFFFFFFFF8

        uint8_t *ptr8_dest = (uint8_t *)dest;
        const uint8_t *ptr8_src = (const uint8_t *)src;

        for (size_t i = start; i < count; i++) {
            ptr8_dest[i] = ptr8_src[i];
        }
        return dest;
    } else {
        uint8_t *ptr_dest = (uint8_t *)dest;
        const uint8_t *ptr_src = (const uint8_t *)src;

        for (size_t i = 0; i < count; i++) {
            ptr_dest[i] = ptr_src[i];
        }

        return dest;
    }
}