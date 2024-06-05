#include <stdio.h>
#include "small_bits.h"

int main(int argc, char* argv[]) {
  for (size_t w = 1; w < 16; ++w) {
    uint64_t m = 1 << (w-1);
    for (uint64_t i = 0; i < m; ++i) {
      uint64_t x = small_from64(w,i);
      for (uint64_t mo = 1; mo < m; ++mo) {
        uint64_t y = small_from64(w,mo);
      }
    }
  }
  return 0;
}
