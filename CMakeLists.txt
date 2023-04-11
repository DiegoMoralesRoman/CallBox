cmake_minimum_required(VERSION 3.10)

project(Protocol)

# Specify standatd
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Libraries
add_subdirectory(src)
include_directories(src)

set (LINUX_FILES serial_port.hpp serial_port.cpp)

add_compile_options(-Wall)

# Custom targets
add_custom_target(run
    COMMAND ./Protocol
    DEPENDS ./Protocol)

add_executable(ProtocolV3_TX main_tx.cpp ${LINUX_FILES})
add_executable(ProtocolV3_RX main_rx.cpp ${LINUX_FILES})
add_executable(Server server.cpp ${LINUX_FILES})

target_link_libraries(ProtocolV3_TX protocol -lpthread)
target_link_libraries(ProtocolV3_RX protocol -lpthread)
target_link_libraries(Server protocol -lpthread)

add_custom_target(check
    COMMAND cppcheck --std=c++17 --enable=all --inconclusive --inline-suppr ../src
    DEPENDS)

add_custom_target(docs
    COMMAND doxygen ../docs/config-file)

# Testing
find_package(doctest REQUIRED)
file(GLOB_RECURSE TEST_FILES "tests/*.cpp")
add_executable(tests ${TEST_FILES})
target_link_libraries(tests doctest::doctest protocol)

add_custom_target(test
    COMMAND ./tests
    DEPENDS tests)
