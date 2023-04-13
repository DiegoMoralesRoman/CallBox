#include <doctest/doctest.h>

#include "protocol.hpp"

constexpr size_t BUFFER_SIZE = 24;

TEST_CASE("int8 serialization") {
  callbox::serial::Int8 value = 123;
  CHECK_EQ(value, 123);

  char buffer[BUFFER_SIZE] = {0};
  callbox::serial::SerialBuffer serial_buffer(buffer, BUFFER_SIZE);

  auto new_buffer = value.serialize(serial_buffer);

  value = 14;
  value.serialize(new_buffer);

  CHECK_EQ(serial_buffer[0], 123);
  CHECK_EQ(serial_buffer[1], 14);
}

TEST_CASE("int8 deserialization") {
  callbox::serial::Int8 value;
  CHECK_EQ(value, 0);

  char buffer[BUFFER_SIZE] = {123, 14};
  callbox::serial::SerialBuffer serial_buffer(buffer, BUFFER_SIZE);

  auto new_buffer = value.deserialize(serial_buffer);
  CHECK_EQ(static_cast<callbox::serial::Int8::Underlying_t>(value), 123);

  value.deserialize(new_buffer);
  CHECK_EQ(static_cast<callbox::serial::Int8::Underlying_t>(value), 14);
}

