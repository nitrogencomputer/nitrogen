cmake_minimum_required(VERSION 3.14)
project(bloque CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(nitrogen 
              src/main.cpp
              src/block/block.cpp 
              src/blockchain/blockchain.cpp 
              src/p2p/sockets/nitrogen_client.cpp 
              src/p2p/sockets/nitrogen_server.cpp 
              )

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
              
add_executable(nitrogen_tests 
              src/block/block_test.cpp
              src/block/block.cpp 
              src/blockchain/blockchain.cpp 
              )

target_compile_definitions(nitrogen_tests PRIVATE TEST_BUILD)
target_link_libraries(
    nitrogen_tests
    ${GTEST_LIBRARIES}
    pthread
)

include(GoogleTest)
gtest_discover_tests(nitrogen_tests)
