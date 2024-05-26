#include <endian.h>
#include "large_bits.h"

#include <stdio.h>

// For bit sizes 65 ..

void from32(size_t w, uint32_t x, uint32_t *out)
{
  out[0] = x << PADDING_BITS_FOR_BITS(w);
}

void from64(size_t bits, uint64_t x, uint32_t *out)
{
  if (bits > 32) {
    out[1] = x >> 32;
    bits -= 32;
  }
  from32(bits, x, out);
}

void from_bytes_be(size_t bits, const char *in, uint32_t *out)
{
  size_t len = SIZE_FOR_BITS(bits);
  const uint32_t *in32 = (const uint32_t*) in;
  const uint16_t *in16 = (const uint16_t*) in;

  size_t index = 0;
  while (bits >= 32) {
    out[len - 1 - index] = be32toh(in32[index]);
    ++index;
    bits -= 32;
  }

  if (bits >= 16) {
    index <<= 2;
    out[0] = ((uint32_t)be16toh(in16[index])) << 16;
    bits -= 16;
    index += 1;
  }

  if (bits > 8) {
    out[0] |= ((uint32_t)be16toh(in16[index])) << (16 - bits);
  } else {
    if (bits > 0) {
      index <<= 2;
      out[0] |= ((uint32_t)in[index]) << (16 - bits);
    }
  }
}


char* show_byte_hex(uint8_t byte, char* out) {
  static const char* digits = "0123456789abcdef";
  *out++ = digits[byte >> 4];
  *out++ = digits[byte & 0xF];
  return out;
}

void show_hex(size_t bits, const uint32_t *in, char* out) {
  size_t padding = PADDING_BITS_FOR_BITS(bits);
  if (padding == 0) {
    for (size_t i = SIZE_FOR_BITS(bits); i > 0; --i) {
      uint32_t x = in[i-1];
      out = show_byte_hex(x >> 24, out);
      out = show_byte_hex(x >> 16, out);
      out = show_byte_hex(x >>  8, out);
      out = show_byte_hex(x,       out);
    }
  } else {
      printf("XXX\n");
  }
}


void add(size_t bits, const uint32_t *x, const uint32_t *y, uint32_t *out)
{
  size_t len = SIZE_FOR_BITS(bits);
  uint64_t buf = 0;
  for (size_t index = 0; index < len; ++index) {
    buf += x[index];
    buf += y[index];
    out[index] = buf;
    buf >>= 32;
  }
}


