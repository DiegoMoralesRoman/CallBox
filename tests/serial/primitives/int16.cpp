#include <doctest/doctest.h>

#include "protocol.hpp"

constexpr size_t BUFFER_SIZE = 24;

TEST_CASE("int16 serialization") {
  callbox::serial::Int16 value = 12345;
  CHECK_EQ(value, 12345);

  char buffer[BUFFER_SIZE] = {0};
  callbox::serial::SerialBuffer serial_buffer(buffer, BUFFER_SIZE);

  auto new_buffer = value.serialize(serial_buffer);

  value = 4321;
  value.serialize(new_buffer);

  CHECK_EQ(serial_buffer[0], 57);
  CHECK_EQ(serial_buffer[1], 48);
  CHECK_EQ(serial_buffer[2], -31);
  CHECK_EQ(serial_buffer[3], 16);
}

TEST_CASE("int16 deserialization") {
  callbox::serial::Int16 value;
  CHECK_EQ(value, 0);

  char buffer[BUFFER_SIZE] = {57, 48, -31, 16};
  callbox::serial::SerialBuffer serial_buffer(buffer, BUFFER_SIZE);

  auto new_buffer = value.deserialize(serial_buffer);
  CHECK_EQ(static_cast<callbox::serial::Int16::Underlying_t>(value), 12345);

  value.deserialize(new_buffer);
  CHECK_EQ(static_cast<callbox::serial::Int16::Underlying_t>(value), 4321);
}


