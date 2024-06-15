#ifndef SMALL_BITS_H
#define SMALL_BITS_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

// Global invariant: widths 1 .. 64


static inline
size_t small_padding(size_t w) { return 64 - w; }

static inline
uint64_t small_normalize(size_t w, uint64_t x) {
  uint64_t mask = UINT64_C(-1) << small_padding(w);
  return x & mask;
}


/* Conversions */

static inline
uint64_t small_to_u64(size_t w, uint64_t x) { return x >> small_padding(w); }

static inline
int64_t u2i_64(uint64_t x) {
  if (x <= (uint64_t)INT64_MAX) return x;
  uint64_t lim = INT64_MIN;
  if (x >= lim) return (int64_t)(x - lim) + INT64_MIN;
  assert(false);
}

static inline
int64_t small_to_i64(size_t w, uint64_t x) {
  int64_t sx = u2i_64(x);
  return sx >> small_padding(w);
}

static inline
uint64_t small_from64(size_t w, uint64_t x) {
  return x << small_padding(w);
}


/* Arithmetic */

static inline
uint64_t small_add(size_t _w, uint64_t x, uint64_t y) { return x + y; }

static inline
uint64_t small_sub(size_t _w, uint64_t x, uint64_t y) { return x - y; }

static inline
uint64_t small_neg(size_t _w, uint64_t x) { return -x; }

static inline
uint64_t small_mul(size_t w, uint64_t x, uint64_t y) {
  return x * small_to_u64(w,y);
}

static inline
uint64_t small_div(size_t w, uint64_t x, uint64_t y) {
  return small_normalize(w,x / small_to_u64(w,y));
}

static inline
uint64_t small_mod(size_t w, uint64_t x, uint64_t y) {
  return small_from64(w, small_to_u64(w,x) % small_to_u64(w,y));
}

// Signed division.  Throws exception if y is 0. 
// If y is (-1) may wrap around.
static inline
uint64_t small_sdiv(size_t w, uint64_t x, uint64_t y) {
  int64_t b = small_to_i64(w,y);
  if (b == INT64_C(-1)) return small_neg(w,x);
  int64_t a = small_to_i64(w,x);
  return small_from64(w,a / b);
}

// Signed modulus. Throws exception if y is 0.
static inline
uint64_t small_smod(size_t w, uint64_t x, uint64_t y) {
  int64_t b = small_to_i64(w,y);
  if (b == INT64_C(-1)) return 0;
  int64_t a = small_to_i64(w,x);
  return small_from64(w, a % b);
}



/* Bitwise operations */

static inline
uint64_t small_and(size_t _w, uint64_t x, uint64_t y) { return x & y; }

static inline
uint64_t small_or(size_t _w, uint64_t x, uint64_t y) { return x | y; }

static inline
uint64_t small_xor(size_t _w, uint64_t x, uint64_t y) { return x ^ y; }



/* Comparisons */

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
  return u2i_64(x) < u2i_64(y);
}

static inline
bool small_sleq(size_t _w, uint64_t x, uint64_t y) {
  return u2i_64(x) <= u2i_64(y);
}


/* Shift and Rotates */

static inline
uint64_t small_shift_left(size_t w, uint64_t x, size_t y) {
  if (y >= w) return 0;
  return x << y;
}

static inline
uint64_t small_ushift_right(size_t w, uint64_t x, size_t y) {
  if (y >= w) return 0;

  return small_normalize(w,x >> y);
}

static inline
uint64_t small_sshift_right(size_t w, uint64_t x, size_t y) {
  int64_t sx = u2i_64(x);
  if (y >= w) return sx >= 0? 0 : small_from64(w,UINT64_C(-1));

  return small_normalize(w,sx >> y);
}

static inline
uint64_t small_rotate_left(size_t w, uint64_t x, size_t y) {
  y %= w;
  return small_normalize(w, (x << y) | (x >> (w - y)));
}

static inline
uint64_t small_rotate_right(size_t w, uint64_t x, size_t y) {
  y %= w;
  return small_normalize(w, (x << (w - y)) | (x >> y));
}





/* Splitting and Joining */

// n <= w
static inline
uint64_t small_take(size_t w, size_t n, uint64_t x) {
  return small_normalize(n, x);
}

// n <= w
static inline
uint64_t small_drop(size_t w, size_t n, uint64_t x) {
  return x << n;
}

// w1 + w2 <= 64
static inline
uint64_t small_append(size_t w1, size_t w2, uint64_t x, uint64_t y) {
  return x | (y >> w1);
}





/* Iterators */
// XXX


#endif
