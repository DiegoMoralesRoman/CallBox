#pragma once

#include "serial_buffer.hpp"
#include "../utils.hpp"

namespace callbox::serial {
  using ID_t = uint8_t;

  ///
  /// @brief Base serializable class
  ///
  /// @details
  /// All components that can be sent through the protocol have to inherit from this class.
  ///
  class Serializable {
    public:
      ///
      /// @brief Copies the serializable element into the buffer (serial -> buffer)
      /// @param buffer Buffer to copy the data to
      /// @return New buffer positioned next to the written data
      ///
      virtual SerialBuffer serialize(SerialBuffer& buffer) const = 0;

      ///
      /// @brief Generated a type from the specified buffer (buffer -> serial)
      /// @param buffer Buffer to copy the data from
      /// @return New buffer positioned next to the read data
      ///
      virtual SerialBuffer deserialize(const SerialBuffer& buffer) = 0;

      ///
      /// @brief Size that the serialized data would have
      /// @return Size in bytes of the serialized data
      ///
      virtual size_t size() const = 0;

      ///
      /// @brief Size of the serialized data (NOT dynamic)
      /// @return Size of the serialized data (NOT dynamix)
      /// @details 
      /// This method is valid for data types that are not dynamic (like Int8, Bool) unlike String.
      /// So this method should be used with caution
      ///
      static size_t static_size();

      ///
      /// @brief Type ID of the serializable
      /// @return Unique identifier for the serializable
      /// @details
      /// # Recommended way of generating identifiers
      /// The identifiers are like a liked list of ```enum```. Each enum that contains identifiers
      /// for data types, also contains a element ```SIZE```. And stablishing the first element of the
      /// next enum to the previous ```SIZE``` would make it so that the first element of the new ```enum```
      /// starts with the next value that the first enum would have.
      ///
      /// ```cpp
      /// enum IDs_a {
      ///   A,                // A = 0
      ///   B,                // B = 1
      ///   C,                // C = 2
      ///   LAST              // LAST = 3
      /// };
      ///
      /// enum IDs_b {
      ///   A = IDs_a::LAST,  // A = 3
      ///   B,                // B = 4
      ///   C                 // C = 5
      /// }
      /// ```
      ///
      /// Although this code wouldnt work because of namespaces collision. In won't be a problem inside the
      /// library because of the different namespaces;
      ///
      virtual ID_t type_id() const = 0;
    private:
  };

}
