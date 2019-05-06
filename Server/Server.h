#ifndef BEEPER_SERVER_H
#define BEEPER_SERVER_H

#include <atomic>
#include "../src/TCPListener.h"
#include "../src/Selector.h"
#include "ClientMonitor.h"


class Server {
    friend class ClientMonitor;
    std::atomic<bool> running;
    TCPListener listener;
    void communicationThreadTask();
public:
    Selector selector;
    ClientMonitor clientMonitor;

    Server();
    void start(Address, int);
    void stop();
    bool isRunning();
};

#endif //BEEPER_SERVER_H
