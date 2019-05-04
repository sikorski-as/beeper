#ifndef BEEPER_SERVER_H
#define BEEPER_SERVER_H

#include <atomic>
#include "../src/TCPListener.h"
#include "../src/Selector.h"
#include "ClientMonitor.h"


class Server {
    std::atomic<bool> running;
    TCPListener listener;
    Selector selector;
    void communicationThreadTask();
public:
    ClientMonitor clientMonitor;

    Server();
    void start(Address, int);
    void stop();
    bool isRunning();
};

#endif //BEEPER_SERVER_H
