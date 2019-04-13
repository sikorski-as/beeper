#ifndef BEEPER_TCPSOCKET_H
#define BEEPER_TCPSOCKET_H

#include "Socket.h"
#include "TCPListener.h"
#include "Address.h"

class TCPListener;
class TCPSocket : public Socket
{
    friend class TCPListener; // so TCPListener can create TCPSockets for clients providing descriptor
protected:
    bool hasRemote;
    TCPSocket(int socketDescriptor);
    TCPSocket();
public:
    Address getRemoteAddress();
    //virtual ssize_t readn(std::size_t n, char* buffer);
    //virtual ssize_t writen(std::size_t n, const char* buffer);

    int send(int size, const char * buffer);
    int receive(int size, char * buffer);
};

#endif //BEEPER_TCPSOCKET_H
