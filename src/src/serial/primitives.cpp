#include "serial/primitives.hpp"
#include "serial/serializable.hpp"

using namespace callbox::serial;

const bool IS_LITTLE_ENDIAN = callbox::utils::is_little_endian();

// ==================================================
// INT
// ==================================================

template<typename Base>
SerialBuffer Int<Base>::serialize(SerialBuffer &buffer) const {
  auto array = reinterpret_cast<const char*>(&m_value);
  if (IS_LITTLE_ENDIAN) {
    for (size_t i = 0; i < sizeof(Base); i++) {
      buffer[i] = array[sizeof(Base) - 1 - i];
    }
  } else {
    for (size_t i = 0; i < sizeof(Base); i++) {
      buffer[i] = array[i];
    }
  }
  return buffer + sizeof(Base);
}

template<typename Base>
SerialBuffer Int<Base>::deserialize(const SerialBuffer &buffer) {
  auto array = reinterpret_cast<char*>(&m_value);
  if (IS_LITTLE_ENDIAN) {
    for (size_t i = 0; i < sizeof(Base); i++) {
      array[i] = buffer[sizeof(Base) - 1 - i];
    }
  } else {
    for (size_t i = 0; i < sizeof(Base); i++) {
      array[i] = buffer[i];
    }
  }
  return buffer + sizeof(Base);
}

template<typename Base>
size_t Int<Base>::size() const {
  return static_size();
}

template<typename Base>
size_t Int<Base>::static_size() {
  return sizeof(m_value);
}

// TypeID specific instantiation
template<>
ID_t Int<int8_t>::type_id() const {
  return PrimitiveIDs::INT8;
}

template<>
ID_t Int<int16_t>::type_id() const {
  return PrimitiveIDs::INT16;
}

template<>
ID_t Int<int32_t>::type_id() const {
  return PrimitiveIDs::INT32;
}

template<>
ID_t Int<int64_t>::type_id() const {
  return PrimitiveIDs::INT64;
}
