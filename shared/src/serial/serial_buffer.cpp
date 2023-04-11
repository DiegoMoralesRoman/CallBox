#include "serial/serial_buffer.hpp"

using namespace protouart::serial;

SerialBuffer::SerialBuffer(char *const start, const size_t len)
  : m_start(start), m_len(len) {
  m_current_pos = 0;
}

SerialBuffer::SerialBuffer(char *const start, const size_t len, const size_t pos)
  : m_start(start), m_len(len), m_current_pos(pos) {

}

char& SerialBuffer::operator[](const size_t index) {
  size_t wrapped_index = (index + m_current_pos) % m_len;
  return m_start[wrapped_index];
}

char SerialBuffer::operator[](const size_t index) const {
  size_t wrapped_index = (index + m_current_pos) % m_len;
  return m_start[wrapped_index];
}

void SerialBuffer::shift(size_t ammount) {
  
}

SerialBuffer SerialBuffer::operator+(size_t ammount) {
  size_t next_pos = (m_current_pos + ammount) % m_len;
  SerialBuffer buffer(m_start, m_len, next_pos);
  return buffer;
}

void SerialBuffer::operator+=(size_t ammount) {
  m_current_pos = (m_current_pos + ammount) % m_len;
}
