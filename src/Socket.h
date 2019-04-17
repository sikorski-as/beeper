#ifndef BEEPER_SOCKET_H
#define BEEPER_SOCKET_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <exception>
#include <string>
#include "Address.h"
#include "Selector.h"

class Selector;

class Socket 
{
public:
    friend class Selector;
    Address getLocalAddress();
    bool operator==(const Socket&);
    void close();
protected:
    int socketDescriptor;
    Socket();
    Socket(int newSocketDescriptor);
};

#endif //BEEPER_SOCKET_H
