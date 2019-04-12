cmake_minimum_required(VERSION 3.9)
project(beeper)

set(CMAKE_CXX_STANDARD 11)

add_executable(beeper_server Server/server.cpp src/Socket.h Server/TCPListener.cpp Server/TCPListener.h src/Socket.cpp
        Client/TCPSocket.h Client/TCPSocket.cpp)
add_executable(beeper_client Client/client.cpp src/Socket.h Client/TCPSocket.cpp Client/TCPSocket.h
        src/Socket.cpp Client/TCPClientSocket.cpp Client/TCPClientSocket.h)