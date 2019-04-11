cmake_minimum_required(VERSION 3.9)
project(beeper)

set(CMAKE_CXX_STANDARD 11)

add_executable(beeper_server Server/server.cpp src/ISocket.h src/Socket.cpp src/Socket.h)
add_executable(beeper_client Client/client.cpp)