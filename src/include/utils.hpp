#pragma once

#include <stdint.h>

#ifdef NO_STL 
   #ifdef ARDUINO_BUILD
      #include <Arduino.h>
      namespace callbox {
         using string = String;
      }
   #endif
#else
   #include <string>
   namespace callbox {
      using string = std::string;
   }
#endif

namespace callbox::utils
{
  const bool is_little_endian();
  // Functions
  using hash_t = uint32_t;

  /**
   * @brief Generates a 
   */
  constexpr hash_t hash_uint32(const hash_t value)
  {
     hash_t tmp = value;
     tmp += ~(tmp << 15);
     tmp ^= (tmp >> 10);
     tmp += (tmp << 3);
     tmp ^= (tmp >> 6);
     tmp += ~(tmp << 11);
     tmp ^= (tmp >> 16);
     return tmp;
  }

  hash_t calculate_hash(const char *const ptr, uint8_t len);

  // Constexpr string hash calculation (it has to be in the header file)
  constexpr hash_t hash_string(const char *ptr)
  {
     /*
     Because this implememtation uses a 32bit hashing function and because the byte array that will be
     hashed doesn't have to have a length divisible by 4 (32bit) there could be some spare bytes left
     This can be seen on the following diagram:
     [][][][] [][][][] [][][]--
     -------- -------- --------
        B0       B1       B2
     Blocks 0 and 1 are full, but block 2 is only 3 bytes, so the 1 byte at the end has to be accounted
     for. If nothing was done there could be a segmentation fault (that one byte is outside the array).
     */

     // Base hashing function
     auto hash = hash_uint32;

     // Temporal variable for hash calculation (this variable will be the one returned)
     hash_t final_hash = 0;

     hash_t tmp_buff = 0;
     hash_t index = 0;
     while (ptr[index])
     {
        hash_t local_index = index % sizeof(hash_t);

        hash_t value = (hash_t)ptr[index] << (local_index * 8);
        tmp_buff |= value;

        if (local_index == 0)
        {
           final_hash ^= hash(tmp_buff);
           tmp_buff = 0;
        }

        index++;
     }
     if (((index - 1) % sizeof(hash_t)) != 0)
        final_hash ^= hash(tmp_buff);

     return final_hash;
  }
} // namespace protouart::utils
