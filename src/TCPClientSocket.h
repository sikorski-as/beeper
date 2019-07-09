#ifndef BEEPER_TCPCLIENTSOCKET_H
#define BEEPER_TCPCLIENTSOCKET_H

#include "TCPSocket.h"
#include "Address.h"

class TCPClientSocket : public TCPSocket
{
public:
    TCPClientSocket();
    void connect(Address remote);
};

#endif //BEEPER_TCPCLIENTSOCKET_H
