#ifndef SMALL_BITS_H
#define SMALL_BITS_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

// For bits sizes 1 .. 64

static inline
size_t small_padding(size_t w) { return 64 - w; }

static inline
uint64_t small_normalize(size_t w, uint64_t x) {
  uint64_t mask = UINT64_C(-1) << small_padding(w);
  return x & mask;
}

static inline
uint64_t small_to64(size_t w, uint64_t x) { return x >> small_padding(w); }

static inline
uint64_t small_from64(size_t w, uint64_t x) {
  return x << small_padding(w);
}

static inline
uint64_t small_add(size_t _w, uint64_t x, uint64_t y) { return x + y; }

static inline
uint64_t small_sub(size_t _w, uint64_t x, uint64_t y) { return x - y; }

static inline
uint64_t small_neg(size_t _w, uint64_t x) { return -x; }

static inline
uint64_t small_mul(size_t w, uint64_t x, uint64_t y) {
  return x * small_to64(w,y);
}

static inline
uint64_t small_div(size_t w, uint64_t x, uint64_t y) {
  return small_normalize(w,x / small_to64(w,y));
}

static inline
uint64_t small_mod(size_t w, uint64_t x, uint64_t y) {
  return small_from64(w, small_to64(w,x) % small_to64(w,y));
}




static inline
uint64_t small_and(size_t _w, uint64_t x, uint64_t y) { return x & y; }

static inline
uint64_t small_or(size_t _w, uint64_t x, uint64_t y) { return x | y; }

static inline
uint64_t small_xor(size_t _w, uint64_t x, uint64_t y) { return x ^ y; }




static inline
bool small_eq(size_t _w, uint64_t x, uint64_t y) { return x == y; }

static inline
bool small_neq(size_t _w, uint64_t x, uint64_t y) { return x != y; }



static inline
bool small_lt(size_t _w, uint64_t x, uint64_t y) { return x < y; }

static inline
bool small_leq(size_t _w, uint64_t x, uint64_t y) { return x <= y; }

static inline
bool small_slt(size_t _w, uint64_t x, uint64_t y) {
  return (int64_t)x < (int64_t)y;
}

static inline
bool small_sleq(size_t _w, uint64_t x, uint64_t y) {
  return (int64_t)x <= (int64_t)y;
}




#endif