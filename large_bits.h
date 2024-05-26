#ifndef LARGE_BITS_H
#define LARGE_BITS_H

#include <stdint.h>
#include <stddef.h>

#define SIZE_FOR_BITS(bits)          ((bits + 31) / 32)
#define PADDING_BITS_FOR_BITS(bits)  (bits % 32)
#define BYTES_FOR_BITS(bits)         ((bits + 7) / 8)

#define DECLARE_BITS(x,bits) uint32_t x[SIZE_FOR_BITS(bits)]


static inline
void large_normalize(size_t w, uint32_t *in_out) {
  uint32_t mask = UINT32_C(-1) << PADDING_BITS_FOR_BITS(w);
  in_out[0] &= mask;
}



void from32(size_t bits, uint32_t x, uint32_t *out);
void from64(size_t bits, uint64_t x, uint32_t *out);
void from_bytes_be(size_t bits, const char* in, uint32_t *out);

void show_hex(size_t bits, const uint32_t *in, char *out);

void add(size_t bits, const uint32_t *x, const uint32_t *y, uint32_t *out);

#endif
