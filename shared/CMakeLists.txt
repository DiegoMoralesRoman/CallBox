set(HEADERS 
  serial/serial
  serial/base128
  serial/serial_buffer
  serial/primitives
  serial/serializable
)
set(SOURCES
  serial/base128
  serial/serial_buffer
  serial/primitives
  utils
)

include_directories(include)


list(TRANSFORM HEADERS PREPEND include/)
list(TRANSFORM SOURCES PREPEND src/)
list(TRANSFORM HEADERS APPEND .hpp)
list(TRANSFORM SOURCES APPEND .cpp)

add_library(protocol ${HEADERS} ${SOURCES} protocol.hpp) 
set_target_properties(protocol PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(protocol)
