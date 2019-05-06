#ifndef BEEPER_CLIENT_H
#define BEEPER_CLIENT_H

#include <string>
#include <thread>
#include "../src/IONotifiable.h"
#include "../src/TCPSocket.h"
#include "../src/CommunicationStack.h"
#include "Event.h"

class Client : public IONotifiable{
    std::string username;
    CommunicationStack * communicationStack;

    std::thread clientThread;
    void clientThreadTask();
public:
    Client(CommunicationStack*);
    ~Client();


    std::string getUsername();

    void notifyRead() override;
    void notifyWrite() override;
};


#endif //BEEPER_CLIENT_H
