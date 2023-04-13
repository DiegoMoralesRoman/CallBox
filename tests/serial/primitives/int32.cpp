#include <doctest/doctest.h>

#include "protocol.hpp"

constexpr size_t BUFFER_SIZE = 24;

TEST_CASE("int32 serialization") {
  callbox::serial::Int32 value = 123456789;
  CHECK_EQ(static_cast<callbox::serial::Int32::Underlying_t>(value), 123456789);

  char buffer[BUFFER_SIZE] = {0};
  callbox::serial::SerialBuffer serial_buffer(buffer, BUFFER_SIZE);

  value.serialize(serial_buffer);

  CHECK_EQ(serial_buffer[0], 21);
  CHECK_EQ(serial_buffer[1], -51);
  CHECK_EQ(serial_buffer[2], 91);
  CHECK_EQ(serial_buffer[3], 7);
}

TEST_CASE("int32 deserialization") {
  callbox::serial::Int32 value;
  CHECK_EQ(value, 0);

  char buffer[BUFFER_SIZE] = {21, -51, 91, 7};
  callbox::serial::SerialBuffer serial_buffer(buffer, BUFFER_SIZE);

  value.deserialize(serial_buffer);
  CHECK_EQ(static_cast<callbox::serial::Int32::Underlying_t>(value), 123456789);
}


