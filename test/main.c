#include "small_bits.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
  size_t w = 5;
  size_t r = 19;
  size_t x = small_from64(w,1);
  printf("%lu -> %lu\n", small_to_u64(w,x), small_to_u64(w,small_rotate_right(w,x,r)));
  return 0;
}
