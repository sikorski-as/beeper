#ifndef BEEPER_CLIENTHANDLER_H
#define BEEPER_CLIENTHANDLER_H

#include <mutex>
#include <memory>
#include "../src/TCPSocket.h"
#include "../src/Buffer.h"
#include "../src/Socket.h"

class ClientHandler {
public:
    TCPSocket socket;

    Buffer incomingBuffer;
    std::unique_ptr<std::mutex> incomingBufferAccess;

    Buffer outgoingBuffer;
    std::unique_ptr<std::mutex> outgoingBufferAccess;

    bool shouldEcho = false;

    ClientHandler(TCPSocket);
    ClientHandler(ClientHandler&&) = default;
    ~ClientHandler();
};


class Client{
public:

};


#endif //BEEPER_CLIENTHANDLER_H
