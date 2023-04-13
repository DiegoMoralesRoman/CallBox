#include "utils.hpp"


const bool callbox::utils::is_little_endian() {
  union {
    [[maybe_unused]] uint32_t i;
    char c[4];
  } bint = {0x01020304};

    return bint.c[0] == 1;
}
