cmake_minimum_required(VERSION 3.9)
project(beeper)

set(CMAKE_CXX_STANDARD 11)

add_executable( beeper_server
        Server/main.cpp

        src/Socket.cpp src/Socket.h
        src/Address.cpp src/Address.h
        src/Selector.cpp src/Selector.h
        src/TCPListener.cpp src/TCPListener.h
        src/TCPSocket.cpp src/TCPSocket.h
        src/Buffer.cpp src/Buffer.h

        Server/Server.cpp Server/Server.h
        Server/ClientMonitor.cpp Server/ClientMonitor.h
        Server/Client.cpp Server/Client.h
        src/Event.cpp src/Event.h
        src/IONotifiable.h
        src/CommunicationStack.h
        src/TCPCommunicationStack.cpp src/TCPCommunicationStack.h
        src/SerializationLayer.cpp src/SerializationLayer.h
        src/PacketHandler.h
        src/monitor.h
        src/SynchronizedQueue.h
        src/TCPLayer.cpp src/TCPLayer.h

        src/json.hpp
        sqlite3/sqlite3.h sqlite3/sqlite3.c sqlite3/sqlite3ext.h
        src/Database.cpp src/Database.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
include_directories(${CMAKE_CURRENT_LIST_DIR}/sqlite3)
target_link_libraries(beeper_server Threads::Threads pthread dl)

add_executable( beeper_client
        Client/main.cpp

        src/Socket.cpp src/Socket.h
        src/Address.cpp src/Address.h

        src/TCPSocket.cpp src/TCPSocket.h
        src/TCPClientSocket.cpp src/TCPClientSocket.h
        src/Buffer.cpp src/Buffer.h

        src/IONotifiable.h
        src/CommunicationStack.h
        src/TCPCommunicationStack.cpp src/TCPCommunicationStack.h
        src/SerializationLayer.cpp src/SerializationLayer.h
        src/PacketHandler.h
        src/monitor.h
        src/SynchronizedQueue.h
        src/TCPLayer.cpp src/TCPLayer.h
        src/Event.cpp src/Event.h

        src/json.hpp
        )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(beeper_client Threads::Threads)