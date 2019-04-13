#ifndef BEEPER_TCPLISTENER_H
#define BEEPER_TCPLISTENER_H

#include <cstddef>
#include "Socket.h"
#include "Address.h"
#include "TCPSocket.h"

class TCPSocket;
class TCPListener : public Socket
{
public:
    TCPListener(Address address); // what local address should be used for the listener

    TCPSocket accept();
    void start(int backlogLength); // length of the incoming connections queue

private:
    bool listening;
    int backlogLength;
};

#endif //BEEPER_TCPLISTENER_H
