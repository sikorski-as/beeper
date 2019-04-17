#include <vector>
#include "Socket.h"

#ifndef BEEPER_SELECTOR_H
#define BEEPER_SELECTOR_H

class Socket;
class Selector {
protected:
    std::vector<int> socketDescriptors;

    fd_set read, write, signal;
    int find(const Socket&);

    bool readSelector;
    bool writeSelector;
    bool signalSelector;
public:
    Selector(bool r = true, bool w = true, bool s = true);
    void setupSelector(bool r = true, bool w = true, bool s = true);
    bool isPresent(const Socket&);
    void add(const Socket&);
    void remove(const Socket&);
    void clear();

    int wait(int timeoutInSeconds = 0); // 0 or less = wait forever

    bool isReadReady(const Socket&);
    bool isWriteReady(const Socket&);
    bool isSignalReady(const Socket&);
};

#endif //BEEPER_SELECTOR_H
