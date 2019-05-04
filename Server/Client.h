#ifndef BEEPER_CLIENT_H
#define BEEPER_CLIENT_H

#include "../src/TCPSocket.h"
#include "Event.h"

class Client{
public:
    Client(TCPSocket&);
    TCPSocket getSocket();
    std::string getUsername();
    void insertIntoQueue(Event);

    void notify();
};


#endif //BEEPER_CLIENT_H
