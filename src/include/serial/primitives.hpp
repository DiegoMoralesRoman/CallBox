#pragma once

#include "serializable.hpp"
#include "../utils.hpp"

namespace callbox::serial {
  enum PrimitiveIDs : ID_t {
    INT8,
    INT16,
    INT32,
    INT64,

    // Don't change this value
    SIZE
  };

  template <typename Base>
  class Int : public virtual Serializable {
    public:
      using Underlying_t = Base;

      SerialBuffer serialize(SerialBuffer &buffer) const override;
      SerialBuffer deserialize(const SerialBuffer &buffer) override;

      size_t size() const override;
      ID_t type_id() const override;

      Int(Underlying_t value) : m_value(value) {}
      Int() : m_value(0) {}
      operator Underlying_t() const { return m_value; }

      static size_t static_size();
    private:
      Underlying_t m_value;
  };

  template class Int<int8_t>;
  template class Int<int16_t>;
  template class Int<int32_t>;
  template class Int<int64_t>;
  using Int8 = Int<int8_t>;
  using Int16 = Int<int16_t>;
  using Int32 = Int<int32_t>;
  using Int64 = Int<int64_t>;

  class String : public virtual Serializable {
    public:
      using Underlying_t = callbox::string;

      SerialBuffer serialize(SerialBuffer &buffer) const override;
      SerialBuffer deserialize(const SerialBuffer &buffer) override;

      size_t size() const override;
      ID_t type_id() const override;

      String(const Underlying_t&& value) : m_value(value) {}
      String(const Underlying_t& value) : m_value(value) {}
      String(const char* value) : m_value(value) {}
      String() : m_value("") {}
      operator Underlying_t() const { return m_value; }

      const char* c_str();

      static size_t static_size();
    private:
        Underlying_t m_value;
  };
}
