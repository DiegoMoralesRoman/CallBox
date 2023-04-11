#include "utils.hpp"


using namespace protouart::utils;

const bool is_little_endian() {
  union {
    uint32_t i;
    char c[4];
  } bint = {0x01020304};

    return bint.c[0] == 1;
}
