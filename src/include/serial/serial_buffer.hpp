#pragma once

#include <cstddef>

namespace callbox::serial {

  ///
  /// @brief Circular buffer adapter 
  ///
  class SerialBuffer {
    public:
      SerialBuffer(char *const start, const size_t len);
      SerialBuffer(char *const start, const size_t len, const size_t pos);

      char& operator[](const size_t index);
      char operator[](const size_t index) const;

      void shift(size_t ammount);

      SerialBuffer operator+(size_t ammount) const;
      void operator+=(size_t ammount);

    private:
      char *const m_start;
      const size_t m_len;

      size_t m_current_pos = 0;
  };
}
