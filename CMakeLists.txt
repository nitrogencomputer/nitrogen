cmake_minimum_required(VERSION 3.14)
project(bloque CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(bloque src/block/block.cpp src/block/block.hpp src/blockchain/blockchain.cpp src/blockchain/blockchain.hpp src/p2p/sockets/nitrogen_server.cpp src/p2p/sockets/nitrogen_server.hpp src/p2p/sockets/nitrogen_client.cpp src/p2p/sockets/nitrogen_client.hpp)