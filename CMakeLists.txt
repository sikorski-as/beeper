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
        src/Buffer.cpp src/Buffer.h
        Server/ClientHandler.cpp Server/ClientHandler.h Server/Client.cpp Server/Client.h Server/CommunicationStack.h Server/Event.cpp Server/Event.h Server/TCPCommunicationStack.cpp Server/TCPCommunicationStack.h src/Serializer.h src/Deserializer.h src/Encryptor.h src/Decryptor.h src/SerializationLayer.cpp src/SerializationLayer.h src/EncryptionLayer.cpp src/EncryptionLayer.h src/InCommunicationLayer.h src/OutCommunicationLayer.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(beeper_server Threads::Threads)

add_executable(beeper_client
        Client/client.cpp

        src/Socket.cpp src/Socket.h
        src/Address.cpp src/Address.h

        src/TCPSocket.cpp src/TCPSocket.h
        src/TCPClientSocket.cpp src/TCPClientSocket.h
        src/Buffer.cpp src/Buffer.h)