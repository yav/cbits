#include "small_bits.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
  size_t w = 5;
  uint64_t a = small_from64(w,UINT64_C(-16));
  uint64_t b = small_from64(w,UINT64_C(-1));
  printf("%ld\n", small_to_i64(w,small_sdiv(w,a,b)));
  return 0;
}
