#include <doctest/doctest.h>
#include <protocol.hpp>

#include <iostream>

#include <exception>

constexpr size_t BUFF_SIZE = 64;

TEST_CASE("normal operation") {
  char buffer[BUFF_SIZE] = {0};
  protouart::serial::SerialBuffer serial_buffer(buffer, sizeof(buffer));

  serial_buffer[3] = 14;
  CHECK_EQ(buffer[3], 14);
  CHECK_EQ(serial_buffer[3], 14);
}

TEST_CASE("wrap operation") {
  char buffer[BUFF_SIZE] = {0};
  protouart::serial::SerialBuffer serial_buffer(buffer, sizeof(buffer));

  serial_buffer[sizeof(buffer) + 15] = 14;
  CHECK_EQ(buffer[15], 14);
  CHECK_EQ(serial_buffer[sizeof(buffer) + 15], 14);
}

TEST_CASE("offset opeation") {
  char buffer[BUFF_SIZE] = {0};
  constexpr size_t OFFSET = 12;

  protouart::serial::SerialBuffer serial_buffer(buffer, sizeof(buffer), OFFSET);
  buffer[OFFSET] = 14;

  CHECK_EQ(serial_buffer[0], 14);
  buffer[OFFSET + 5] = 16;
  CHECK_EQ(serial_buffer[5], 16);
}

void check_operators(size_t offset) {
  char buffer[BUFF_SIZE] = {0};
  for (int i = 0; i < BUFF_SIZE; i++) {
    buffer[i] = i;
  }

  protouart::serial::SerialBuffer serial_buffer(buffer, sizeof(buffer));

  (serial_buffer + offset)[0] = 100;
  CHECK_EQ(buffer[offset % sizeof(buffer)], 100);

  serial_buffer += offset;
  serial_buffer[0] = 111;
  CHECK_EQ(buffer[offset % sizeof(buffer)], 111);
}

TEST_CASE("operators") {
  check_operators(1);
}

TEST_CASE("wrap operators") {
  check_operators(BUFF_SIZE + 5);
}

