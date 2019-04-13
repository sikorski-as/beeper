cmake_minimum_required(VERSION 3.9)
project(beeper)

set(CMAKE_CXX_STANDARD 11)

add_executable(beeper_server
        Server/server.cpp

        src/Socket.cpp src/Socket.h
        src/Address.cpp src/Address.h
        src/Selector.cpp src/Selector.h

        src/TCPListener.cpp src/TCPListener.h
        src/TCPSocket.cpp src/TCPSocket.h
        )
add_executable(beeper_client
        Client/client.cpp

        src/Socket.cpp src/Socket.h
        src/Address.cpp src/Address.h

        src/TCPSocket.cpp src/TCPSocket.h
        src/TCPClientSocket.cpp src/TCPClientSocket.h
        )