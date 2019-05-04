#include <vector>
#include <mutex>

#include "Socket.h"
#include "TCPSocket.h"
#include "TCPListener.h"

#ifndef BEEPER_SELECTOR_H
#define BEEPER_SELECTOR_H

class Socket;
class Selector {
protected:
    std::mutex access; // so selector can act as a monitor

    TCPListener listener;
    std::vector<TCPSocket> sockets;
    fd_set read, write, signal;

    int find(const TCPSocket&);  // not synchronized
    std::vector<int> getSocketDescriptors(); // not synchronized
    bool isPresent(const TCPSocket&);  // not synchronized
public:
    explicit Selector(const TCPListener&);

    void setListener(const TCPListener&);
    bool isListenerReady();

    void add(const TCPSocket&);
    void remove(const TCPSocket&);
    void clear();

    int wait(int timeoutInSeconds = 0); // 0 or less = wait forever

    std::vector<TCPSocket> getReadReadySockets();
    std::vector<TCPSocket> getWriteReadySockets();
};

#endif //BEEPER_SELECTOR_H
