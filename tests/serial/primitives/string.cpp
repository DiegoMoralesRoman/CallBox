#include <doctest/doctest.h>

#include "protocol.hpp"

constexpr size_t BUFF_SIZE = 64;

TEST_CASE("string serialization") {
  callbox::serial::String str = "Kekos";

  char buffer[BUFF_SIZE] = {0};
  callbox::serial::SerialBuffer serial_buffer(buffer, BUFF_SIZE);


}

TEST_CASE("string deserialization") {

}
