cmake_minimum_required(VERSION 3.9)
project(beeper)

set(CMAKE_CXX_STANDARD 11)

add_executable(beeper_server Server/server.cpp src/Socket.h Server/ServerSocket.cpp Server/ServerSocket.h src/Socket.cpp)
add_executable(beeper_client Client/client.cpp src/Socket.h Client/ClientSocket.cpp Client/ClientSocket.h src/Socket.cpp)